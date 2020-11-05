#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSharedPointer>
#include <QTextCodec>
#include "sy_logger.h"
#include "sy_minidump.h"

#include "sy_utils.h"
#include "sy_logger.h"
int main(int argc, char *argv[])
{

#ifdef WIN32
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);//注册异常捕获函数
#endif
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QCoreApplication::setApplicationName("control");
    QCoreApplication::setOrganizationName("CNC");
    QCoreApplication::setOrganizationDomain("cnc.org");

    QGuiApplication app(argc, argv);
    qlogEx(qtr("启动"));
    qWarnxx(qtr("测试日志"), "test");
    qDebugxxx(qtr("测试日志"), "test", "testtest");
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
