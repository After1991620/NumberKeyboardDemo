#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTextCodec>
#include <QQmlContext>
#include "keyboardwakeup.h"
#include "keyboardconfig.h"
#include <QDebug>
#include <QDataStream>

/**
 * 为了使QT能保证只创建一个实例来进行, 对windows和linux分别采取了全局互斥变量和文件锁的方法。
 * Q_OS_WIN32宏用来表示编译运行的目标平台是windows，Q_OS_LINUX则标示目标为linux
 */
/*
#if defined Q_OS_WIN32
#include <windows.h>
bool checkOnly()
{
    //创建互斥量
    HANDLE m_hMutex = CreateMutex(NULL, FALSE, L"keyboard_demo4");
    //检查错误代码
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        //如果已有互斥量存在则释放句柄并复位互斥量
        CloseHandle(m_hMutex);
        m_hMutex = NULL;
        //程序退出
        return false;
    }else{
        return true;
    }
}
#endif
#if defined  Q_OS_LINUX
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
bool checkOnly()
{
    const char fileName[] = "/tmp/lockfile";
    int fd = open (fileName, O_WRONLY | O_CREAT, 0644);
    int flock = lockf(fd, F_TLOCK, 0);
    //给文件加锁
    if(fd == -1){
        perror("open lockfile/n");
        return false;
    }
    //程序退出后，文件自动解锁
    return true;
}
#endif
*/
extern KeyboardWakeUp *g_keyboardWakeup;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    g_keyboardWakeup = new KeyboardWakeUp();

    if(g_keyboardWakeup->init("LessoKeyboard")){
        KeyboardConfig * kbConfig = new KeyboardConfig();


        QQmlApplicationEngine engine;
        engine.rootContext()->setContextProperty("kbConfig",kbConfig);
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        return app.exec();
    }else{
        QLocalSocket ls;
        ls.connectToServer("LessoKeyboard");
        if(ls.waitForConnected()){
            QDataStream ds(&ls);
            ds << true;
            ls.waitForBytesWritten();
        }
        return 0;
    }
}



