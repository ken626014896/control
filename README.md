# control

#### 介绍
简单demo
#### 软件架构
软件架构说明，来自某个大佬的项目结构的修改




#### 使用说明

1.  集成log功能，使用方法如下, 一个x代表一个参数
    qlogEx(qtr("启动"));
    qWarnxx(qtr("测试日志"), "test");
    qDebugxxx(qtr("测试日志"), "test", "testtest");

2.  manager是主要的函数文件，在qml调用函数时，都是通过这个函数的实例来调用


3.  data_info 是基本的数据函数，可以被各种继承

4.  data_model 是列表函数，在qml中使用list时用到，实例看代码

    data_model test;
    manager manager(&test);
    engine.rootContext()->setContextProperty("$manager", &manager);
    engine.rootContext()->setContextProperty("$test", &test);


5. 个人觉得c++到qml核心逻辑代码差不多大概就这些了
#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
