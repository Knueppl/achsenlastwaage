#ifndef ___VEHICLE_H___
#define ___VEHICLE_H___

#include <QPushButton>
#include <QString>
#include <QAction>

#include <ostream>

class Vehicle
{
public:
    Vehicle(void) : _numberOfAxis(0), _tara(0) { }
    Vehicle(const QString& name, const int numberOfAxis, const int tara)
        : _name(name),
          _numberOfAxis(numberOfAxis),
          _tara(tara)
    {

    }

    const QString& name        (void) const { return _name;         }
    int            numberOfAxis(void) const { return _numberOfAxis; }
    int            tara        (void) const { return _tara;         }

private:
    QString _name;
    int     _numberOfAxis;
    int     _tara;
};

typedef Vehicle* VehiclePtr;

Q_DECLARE_METATYPE(VehiclePtr);

inline std::ostream& operator<<(std::ostream& os, const Vehicle& vehicle)
{
    os << "Fahrzeug: " << vehicle.name().toUtf8().data() << ", TATA = " << vehicle.tara() << " mit "
       << vehicle.numberOfAxis() << " Achsen";

    return os;
}

#endif
