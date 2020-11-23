#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSharedPointer>
#include <QTextCodec>
#include "sy_logger.h"
#include "sy_minidump.h"

#include "sy_utils.h"
#include "sy_logger.h"

#include "data_info.h"
#include "manager.h"

#include "data_model.h"
#include "video_item.h"
int main(int argc, char *argv[])
{

#ifdef WIN32
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);//注册异常捕获函数
#endif
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setApplicationName("control");
    QCoreApplication::setOrganizationName("CNC");
    QCoreApplication::setOrganizationDomain("cnc.org");
    qmlRegisterType<video_item>("videoitem", 1, 0, "VideoItem");
    qRegisterMetaType<QSharedPointer<data_info>>("QSharedPointer<data_info>");


    QGuiApplication app(argc, argv);
    qlogEx(qtr("启动"));
    qWarnxx(qtr("测试日志"), "test");
    qDebugxxx(qtr("测试日志"), "test", "testtest");
    QQmlApplicationEngine engine;
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
#if _MSC_VER
    QTextCodec *codec = QTextCodec::codecForName("gbk");
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
#endif
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
#else
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
#endif

    int fontId=QFontDatabase::addApplicationFont(":/font/fontawesome-webfont.ttf");
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);

    data_model test;
    data_model video;
    data_model camera;
    manager manager(&test,&video,&camera);

    engine.rootContext()->setContextProperty("$manager", &manager);
    engine.rootContext()->setContextProperty("$test", &test);
    engine.rootContext()->setContextProperty("$video", &video);
    engine.rootContext()->setContextProperty("$camera", &camera);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
