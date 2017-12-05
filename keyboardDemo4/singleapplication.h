#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <QApplication>
#include <QSharedMemory>
#include <QLocalServer>
#include <QQmlApplicationEngine>


class SingleApplication : public QApplication
{
        Q_OBJECT
    public:
        SingleApplication(int &argc, char **argv);

        bool isRunning();//是否已经有实例在运行
        QQmlApplicationEngine *w;

        //激活窗口
        void _activateWindow();

    private slots:
        //有新连接时触发
        void _newLocalConnection();

    private:
        //初始化本地连接
        void _initLocalConnection();
        //创建服务端
        void _newLocalServer();

        bool _isRunning;
        QLocalServer *_localServer;
        QString _serverName;


};

#endif // SINGLEAPPLICATION_H
