#include "SignalLight.h"

#include <QDebug>

SignalLight::SignalLight(const QString& port, QWidget* parent)
    : QGroupBox("Ampel", parent)
{
    this->setCheckable(true);
    m_portName = port;
    m_port = 0;

    m_mainLayout = new QVBoxLayout(this);
    m_light1 = new LED(Qt::red);
    m_light1->setFixedSize(48, 48);
    m_light2 = new LED(Qt::green);
    m_light2->setFixedSize(48, 48);
    m_mainLayout->addWidget(m_light1);
    m_mainLayout->addWidget(m_light2);

    this->setChecked(false);
    this->setMinimumHeight(100);

    this->connect(this, SIGNAL(clicked(bool)), this, SLOT(enable(bool)));
    this->connect(&m_timer, SIGNAL(timeout()), this, SLOT(breakCommunication()));
}

SignalLight::SignalLight(QWidget* parent)
    : QGroupBox("Ampel", parent)
{
    this->setCheckable(true);
    m_portName = "/dev/ttyUSB0";
    m_port = 0;

    m_mainLayout = new QVBoxLayout(this);
    m_light1 = new LED(Qt::red);
    m_light1->setFixedSize(48, 48);
    m_light2 = new LED(Qt::green);
    m_light2->setFixedSize(48, 48);
    m_mainLayout->addWidget(m_light1);
    m_mainLayout->addWidget(m_light2);

    this->setChecked(false);
    this->setMinimumHeight(100);

    this->connect(this, SIGNAL(clicked(bool)), this, SLOT(enable(bool)));
    this->connect(&m_timer, SIGNAL(timeout()), this, SLOT(breakCommunication()));
}

void SignalLight::enable(bool state)
{
    if (state)
    {
        m_port = new SerialPort(m_portName.toAscii().data());
        m_port->init(B9600);

        this->communicate("remote\r", "remote control");
        this->red();
    }
    else
    {
        this->communicate("close\r", "close remote");
        delete m_port;
    }
}

void SignalLight::breakCommunication(void)
{
    m_stop = true;
}

void SignalLight::communicate(const char* send, const char* receive)
{
    if (!m_port)
    {
        qDebug() << "Ampel nicht initialisiert!";
        return;
    }

    m_stop = false;
    m_port->clearBuffer();
    m_timer.start(1000);
    qDebug() << m_port->sendCString(send) << " Bytes gesendet.";
    int readByte = 0;

    while ((readByte < (int)::strlen(receive)) && !m_stop)
    {
        int tmp;
        if ((tmp = m_port->read()) >= 0)
        {
            readByte += tmp;
            qDebug() << readByte << " Bytes gelesen: " << m_port->getBuffer();
        }
    }

    if (strcmp(receive, m_port->getBuffer().toAscii().data()))
    {
        qDebug() << "Antwort stimmt nicht: " << m_port->getBuffer();
        m_port->readAll();
        m_port->clearBuffer();
    }

    if (m_stop)
    {
        qDebug() << "Keine Antwort!";
    }
}

void SignalLight::red(void)
{
        this->communicate("k1_on\r", "k1_on");
        this->communicate("k2_off\r", "k2_off");
        m_light1->setState(true);
        m_light2->setState(false);
}

void SignalLight::green(void)
{
        this->communicate("k2_on\r", "k2_on");
        this->communicate("k1_off\r", "k1_off");
        m_light1->setState(false);
        m_light2->setState(true);
}
