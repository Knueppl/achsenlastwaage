#include "Fzw12.h"

#include <QDebug>

Fzw12::Fzw12(const char* port)
{
    m_port = new SerialPort(port);
    m_port->init(B9600);

    this->connect(&m_timer, SIGNAL(timeout()), this, SLOT(readPort()));
    this->connect(this, SIGNAL(finished(Weighting*)), this, SLOT(stop(Weighting*)));
}

Fzw12::~Fzw12(void)
{

}

void Fzw12::start(const Vehicle* vehicle, const int goodId, const int supplierId, const int fieldId)
{
    Scale::start(vehicle, goodId, supplierId, fieldId);
    qDebug() << __PRETTY_FUNCTION__;

    m_port->readAll();
    m_port->clearBuffer();
    m_timer.start(250);
}

void Fzw12::readPort(void)
{
    const char* compareString = "Gewicht        :";
    qDebug() << __PRETTY_FUNCTION__;
    m_port->read();
    qDebug() << m_port->getBuffer();

    if (m_port->getBuffer().contains(compareString))
    {
        bool error = false;

        if (m_port->getBuffer().contains("Fehler:"))
        {
            error = true;
        }

        m_port->deleteLeft(m_port->getBuffer().indexOf(compareString) + strlen(compareString));
        const QString tmp(m_port->getBuffer().left(m_port->getBuffer().indexOf("A") - 1));

        this->setNextAxisWeight(tmp.toInt());
    }
}

void Fzw12::stop(Weighting*)
{
    m_timer.stop();
}

void Fzw12::cancel(void)
{
    m_timer.stop();
}
