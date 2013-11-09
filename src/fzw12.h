#ifndef _FZW12_H_
#define _FZW12_H_

#include <iostream>  /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

#include <QString>
#include <QObject>
#include <QTimer>
#include <QWidget>
#include <QGroupBox>

#include "weight_list.h"

#ifdef _DEBUG_
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#endif

class LED : public QWidget
{
public:
    LED(const QColor& color, QWidget* parent = 0);

    void setState(const bool state)
    {
        m_state = state;
        this->update();
    }

    bool state(void) const { return m_state; }

protected:
    void paintEvent(QPaintEvent*);

private:
    bool   m_state;
    QColor m_color;
};

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

class FZW12 : public QObject
{
    Q_OBJECT;

public:
    FZW12(const char* port);

    void newWeight(Weight* weight);
    void abortWeighting(void);

private slots:
    void readPort(void);

signals:
    void finish(Weight*);
    void nextAxis(int, Weight*);

private:
    void completeWeight(void);

    SerialPort* m_port;
    Weight*     m_currentWeight;
    QTimer      m_timer;
};

class SignalLight : public QGroupBox
{
    Q_OBJECT;

public:
    SignalLight(const QString& port, QWidget* parent = 0);

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

#ifdef _DEBUG_

class Dummy : public QWidget
{
    Q_OBJECT;

public:
    Dummy(QWidget* parent = 0);

    void newWeight(Weight* weight);
    void abortWeighting(void);

signals:
    void finish(Weight*);
    void nextAxis(int, Weight*);

private slots:
    void send(void);

private:
    Weight* m_currentWeight;

    QGridLayout* m_mainLayout;
    QPushButton* m_button;
    QSpinBox*    m_weight;
};

#endif
#endif
