#ifndef ___VEHICLE_H___
#define ___VEHICLE_H___

#include <QPushButton>
#include <QString>
#include <QAction>

#include <ostream>

class Vehicle
{
public:
    Vehicle(void)
        : _id(-1),
          _name("unkown"),
          _axes(0),
          _tara(0)
    {

    }
    Vehicle(const QString& name, const int axes, const int tara)
        : _id(-1),
          _name(name),
          _axes(axes),
          _tara(tara)
    {

    }
    Vehicle(const int id, const QString& name, const int axes, const int tara)
        : _id(id),
          _name(name),
          _axes(axes),
          _tara(tara)
    {

    }

    int            id  (void) const { return _id;  }
    const QString& name(void) const { return _name;}
    int            axes(void) const { return _axes;}
    int            tara(void) const { return _tara;}

private:
    int     _id;
    QString _name;
    int     _axes;
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
