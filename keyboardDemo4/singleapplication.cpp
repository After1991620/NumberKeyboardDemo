#include "SingleApplication.h"
#include <QtNetwork/QLocalSocket>
#include <QFileInfo>

#define TIME_OUT (500)

SingleApplication::SingleApplication(int &argc, char **argv)
    : QApplication(argc, argv)
    , w(NULL)
    , _isRunning(false)
    , _localServer(NULL)
{
    //取应用程序名作为LocalServer的名字
    _serverName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    _initLocalConnection();
}

/**
 * 检查是否已经有一个实例在运行
 */
bool SingleApplication::isRunning(){
    return _isRunning;
}

/**
 * 通过socket通讯实现程序单实例运行，监听到新的连接时出发该函数
 */
void SingleApplication::_newLocalConnection(){
    QLocalSocket *socket = _localServer->nextPendingConnection();
    if(socket){
        socket->waitForReadyRead(2*TIME_OUT);
        delete socket;

        _activateWindow();
    }
}

/**
 * 通过socket通讯实现程序单实例运行，
 * 初始化本地连接，如果连接不上server，则创建，否则退出
 */
void SingleApplication::_initLocalConnection(){
    _isRunning = false;

    QLocalSocket socket;
    socket.connectToServer(_serverName);
    if(socket.waitForConnected(TIME_OUT)){
        fprintf(stderr, "%s already running.\n", _serverName.toLocal8Bit().constData());
        _isRunning = true;

        return;
    }

    //连接不上服务器，就创建一个
    _newLocalServer();
}

/**
 * 创建LocalServer
 */
void SingleApplication::_newLocalServer(){
    _localServer = new QLocalServer(this);
    connect(_localServer, SIGNAL(newConnection()), this, SLOT(_newLocalConnection()));
    if(!_localServer->listen(_serverName)){
        //此时监听失败，可能是程序崩溃时，残留进程服务导致的，移除之
        if(_localServer->serverError() == QAbstractSocket::AddressInUseError){
            QLocalServer::removeServer(_serverName);
            _localServer->listen(_serverName);//再次监听
        }
    }
}

/**
 * 激活主窗口
 */
void SingleApplication::_activateWindow(){
    if(w){
        w->load(QUrl(QStringLiteral("qrc:/main.qml")));
    }
}
