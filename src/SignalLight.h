#ifndef ___SIGNAL_LIGHT_H___
#define ___SIGNAL_LIGHT_H___

#include <QGroupBox>
#include <QTimer>
#include <QVBoxLayout>

#include "SerialPort.h"
#include "Led.h"

class SignalLight : public QGroupBox
{
    Q_OBJECT;

public:
    SignalLight(const QString& port, QWidget* parent = 0);
    SignalLight(QWidget* parent = 0);

public slots:
    void green(void);
    void red(void);

private slots:
    void enable(bool);
    void breakCommunication(void);

private:
    void communicate(const char* send, const char* receive);

    SerialPort*  m_port;
    QTimer       m_timer;
    LED*         m_light1;
    LED*         m_light2;
    QVBoxLayout* m_mainLayout;
    QString      m_portName;
    bool         m_stop;
};

#endif
