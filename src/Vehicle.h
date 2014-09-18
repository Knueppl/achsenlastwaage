#ifndef ___VEHICLE_H___
#define ___VEHICLE_H___

#include <QPushButton>
#include <QString>
#include <QAction>

#include <ostream>

struct Vehicle
{
    Vehicle(void) : _numberOfAxis(0), _tara(0) { }

    void setName(const QString& name) { _name = name; }
    void setNumberOfAxis(const int numberOfAxis) { _numberOfAxis = numberOfAxis; }
    void setTara(const int tara) { _tara = tara; }
    void setButton(QPushButton* button) { m_button = button; }
    void setAction(QAction* action) { m_action = action; }
    const QString& name(void) const { return _name; }
    int numberOfAxis(void) const { return _numberOfAxis; }
    int tara(void) const { return _tara; }
    QPushButton* button(void) const { return m_button; }
    QAction* action(void) const { return m_action; }

    QString      _name;
    int          _numberOfAxis;
    int          _tara;
    QPushButton* m_button;
    QAction*     m_action;
};

inline std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle)
{
    os << "Fahrzeug: " << vehicle.name().toUtf8().data() << ", TATA = " << vehicle.tara() << " mit "
       << vehicle.numberOfAxis() << " Achsen";

    return os;
}

#endif
