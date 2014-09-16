#ifndef ___VEHICLE_H___
#define ___VEHICLE_H___

#include <QPushButton>
#include <QString>
#include <QAction>

class Vehicle
{
public:
    Vehicle(void) : m_numberOfAxis(0), m_tara(0) { }

    void setName(const QString& name) { m_name = name; }
    void setNumberOfAxis(const int numberOfAxis) { m_numberOfAxis = numberOfAxis; }
    void setTara(const int tara) { m_tara = tara; }
    void setButton(QPushButton* button) { m_button = button; }
    void setAction(QAction* action) { m_action = action; }
    const QString& name(void) const { return m_name; }
    int numberOfAxis(void) const { return m_numberOfAxis; }
    int tara(void) const { return m_tara; }
    QPushButton* button(void) const { return m_button; }
    QAction* action(void) const { return m_action; }

private:
    QString      m_name;
    int          m_numberOfAxis;
    int          m_tara;
    QPushButton* m_button;
    QAction*     m_action;
};

#endif
