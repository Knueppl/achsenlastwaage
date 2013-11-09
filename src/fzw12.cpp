#include "fzw12.h"
#include <termios.h>
#include <string.h>
#include <QDebug>
#include <QPainter>

/*********************************************************************/
/* Class SerialPort                                                  */
/*********************************************************************/

SerialPort::SerialPort(const char* port)
{
    if ((m_portRef = open(port, O_RDWR | O_NOCTTY | O_NDELAY)) < 0)
    {
        std::cout << "Kann PORT nicht öffnen!" << std::endl;
    }
    else
    {
//        fcntl(m_portRef, F_SETFL, 0);
        fcntl(m_portRef, F_SETFL, FNDELAY);
    }
}

SerialPort::~SerialPort(void)
{
    close(m_portRef);
}

int SerialPort::read(void)
{
    char buffer[512];
    int readChar;

    if ((readChar = ::read(m_portRef, buffer, 512)) > 0)
    {
        buffer[readChar] = '\0';
        m_buffer.append(buffer);
    }

    return readChar;
}

int SerialPort::sendCString(const char* string)
{
    qDebug() << "sendCString(...);";

    return ::write(m_portRef, string, ::strlen(string));
}

void SerialPort::init(speed_t speed)
{
    struct termios options;

    /*
     * Get the current options for the port...
     */

    tcgetattr(m_portRef, &options);

    cfsetispeed(&options, speed);
    cfsetospeed(&options, speed);

    /*
     * Enable the receiver and set local mode...
     */

    options.c_cflag |= (CLOCAL | CREAD);

    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    /*
     * Set the new options for the port...
     */

    tcsetattr(m_portRef, TCSANOW, &options);
}

/*********************************************************************/
/* Class FZW12                                                       */
/*********************************************************************/

FZW12::FZW12(const char* port)
{
    m_port = new SerialPort(port);
    m_port->init(B9600);
    m_currentWeight = NULL;

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(readPort()));
}

void FZW12::newWeight(Weight* weight)
{
    qDebug() << "new Weight(Weight*)";

    m_port->readAll();
    m_port->clearBuffer();
    m_currentWeight = weight;
    m_timer.start(250);
}

int SerialPort::readAll(void)
{
    char buffer[1024];
    int readChar = 0, tmp;

    while ((tmp = ::read(m_portRef, buffer, 1024)) > 0)
    {
        readChar += tmp;
    }

    return readChar;
}

void FZW12::readPort(void)
{
    const char* compareString = "Gewicht        :";
//    qDebug() << "readPort()";
    m_port->read();
//    qDebug() << m_port->getBuffer();

    if (m_currentWeight != NULL && m_port->getBuffer().contains(compareString))
    {
        bool error = false;

        if (m_port->getBuffer().contains("Fehler:"))
        {
            error = true;
        }

        m_port->deleteLeft(m_port->getBuffer().indexOf(compareString) + strlen(compareString));
        QString tmp(m_port->getBuffer().left(m_port->getBuffer().indexOf("A") - 1));

        emit this->nextAxis(tmp.toInt(), m_currentWeight);

        if (m_currentWeight->addAxis(tmp.toInt(), !error) == m_currentWeight->numberOfAxis())
        {
            this->completeWeight();
        }
    }
}

void FZW12::completeWeight(void)
{
    m_timer.stop();
    emit this->finish(m_currentWeight);
    m_currentWeight = NULL;
}

void FZW12::abortWeighting(void)
{
    m_timer.stop();
    delete m_currentWeight;
    m_currentWeight = NULL;
}

/*********************************************************************/
/* Class SignalLight                                                 */
/*********************************************************************/
SignalLight::SignalLight(const QString& port, QWidget* parent) : QGroupBox("Ampel", parent)
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

    connect(this, SIGNAL(clicked(bool)), this, SLOT(enable(bool)));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(breakCommunication()));
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

/*********************************************************************/
/* Class Dummy                                                       */
/*********************************************************************/
LED::LED(const QColor& color, QWidget* parent) : QWidget(parent)
{
    m_state = false;
    m_color = color;
}

void LED::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(this->width(), this->height()));
    if (!this->isEnabled())
    {
        linearGrad.setColorAt(0, Qt::gray);
        linearGrad.setColorAt(1, QColor(Qt::gray).darker());
    }
    else if (m_state)
    {
        linearGrad.setColorAt(0, m_color);
        linearGrad.setColorAt(1, m_color.darker());
    }
    else
    {
        linearGrad.setColorAt(0, m_color.darker(300));
        linearGrad.setColorAt(1, m_color.darker(500));
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(linearGrad));
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(1, 1, this->width() - 2, this->height() - 2);
}

/*********************************************************************/
/* Class Dummy                                                       */
/*********************************************************************/
#ifdef _DEBUG_

Dummy::Dummy(QWidget* parent) : QWidget(parent)
{
    m_mainLayout = new QGridLayout(this);
    this->setWindowTitle("Dummy");

    m_button = new QPushButton("sende");
    m_button->setEnabled(false);
    m_weight = new QSpinBox();
    m_weight->setMaximum(99999);

    m_mainLayout->addWidget(m_weight, 0, 0);
    m_mainLayout->addWidget(m_button, 0, 1);

    connect(m_button, SIGNAL(clicked()), this, SLOT(send()));
}

void Dummy::newWeight(Weight* weight)
{
    m_currentWeight = weight;
    m_button->setEnabled(true);
}

void Dummy::abortWeighting(void)
{
    delete m_currentWeight;
    m_button->setEnabled(false);
}

void Dummy::send(void)
{
    if (m_currentWeight != NULL)
    {
        emit this->nextAxis(m_weight->value(), m_currentWeight);

        if (m_currentWeight->addAxis(m_weight->value(), true) == m_currentWeight->numberOfAxis())
        {
            m_button->setEnabled(false);
            emit finish(m_currentWeight);
            m_currentWeight = NULL;
        }
    }
}

#endif
