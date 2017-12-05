#ifndef KEYBOARDCONFIG_H
#define KEYBOARDCONFIG_H

#include <QObject>

class KeyboardConfig : public QObject
{
    Q_OBJECT


public:
    explicit KeyboardConfig(QObject *parent = 0);
    ~KeyboardConfig();

    Q_PROPERTY(bool kbState READ kbState WRITE setKbState NOTIFY kbStateChanged)

    bool kbState();


signals:
    void kbStateChanged(bool bVal);

public slots:
void setKbState(bool state);

private:
    bool m_kbState;

};

#endif // KEYBOARDCONFIG_H
