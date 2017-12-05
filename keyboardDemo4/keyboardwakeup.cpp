#include "keyboardwakeup.h"
#include <QDataStream>

KeyboardWakeUp *g_keyboardWakeup = NULL;

KeyboardWakeUp::KeyboardWakeUp(QObject *parent) : QObject(parent)
{
    m_server = 0;
}

KeyboardWakeUp::~KeyboardWakeUp(){
    if(m_server){
        delete m_server;
    }
}

bool KeyboardWakeUp::init(const QString &serverName){
    if(isServerRun(serverName)){
        return false;
    }
    m_server = new QLocalServer;

    QLocalServer::removeServer(serverName);
    m_server->listen(serverName);
    connect(m_server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    return true;
}

void KeyboardWakeUp::newConnection(){
    QLocalSocket *newsocket = m_server->nextPendingConnection();
    connect(newsocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void KeyboardWakeUp::readyRead(){
    QLocalSocket *local = static_cast<QLocalSocket *>(sender());
    if(!local)
        return;
    QDataStream in(local);
    bool state;

    in >> state;

//    qDebug() << "readyRead:" << state ;

    emit newMessage(state);


}

bool KeyboardWakeUp::isServerRun(const QString &serverName){
    QLocalSocket ls;
    ls.connectToServer(serverName);
    if(ls.waitForConnected(1000)){
        ls.disconnectFromServer();
        ls.close();
        return true;
    }
    return false;
}
