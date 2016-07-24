#include "SerialPort.h"

#include <QDebug>

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
