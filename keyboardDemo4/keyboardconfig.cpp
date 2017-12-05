#include "keyboardconfig.h"
#include "keyboardwakeup.h"
#include <QDebug>

extern KeyboardWakeUp *g_keyboardWakeup;

KeyboardConfig::KeyboardConfig(QObject *parent) : QObject(parent)
{
    setKbState(true);

    QObject::connect(g_keyboardWakeup, SIGNAL(newMessage(bool)), this, SLOT(setKbState(bool)));
}

KeyboardConfig::~KeyboardConfig(){

}

bool KeyboardConfig::kbState(){
    return m_kbState;
}

void KeyboardConfig::setKbState(bool state){
//    qDebug() << "setKbState" << state;
    m_kbState = state;
    emit kbStateChanged(state);
}
