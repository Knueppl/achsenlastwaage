#ifndef ___SERIAL_PORT_H__
#define ___SERIAL_PORT_H__

#include <iostream>  /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include <QString>

class SerialPort
{
public:
    SerialPort(const char* port);
    ~SerialPort(void);

    int read(void);
    int readAll(void);
    int sendCString(const char* string);
    const QString& getBuffer(void) { return m_buffer; }
    void init(speed_t speed);
    void clearBuffer(void) { m_buffer.clear(); }
    void deleteLeft(const int index) { m_buffer.remove(0, index); }

private:
    int     m_portRef;
    QString m_buffer;
};

#endif
