#ifndef KEYBOARDWAKEUP_H
#define KEYBOARDWAKEUP_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>

class KeyboardWakeUp : public QObject
{
    Q_OBJECT

public:
    explicit KeyboardWakeUp(QObject *parent = 0);
    ~KeyboardWakeUp();
    bool init(const QString &serverName);

signals:
    void newMessage(const bool state);

public slots:
    void newConnection();
    void readyRead();

private:
    QLocalServer *m_server;
    bool isServerRun(const QString &serverName);

};

#endif // KEYBOARDWAKEUP_H
