#ifndef ___VEHICLE_BUTTON_H___
#define ___VEHICLE_BUTTON_H___

#include <QAbstractButton>
#include <QVector>
#include <QPointF>

class QAction;
class Vehicle;

class VehicleButton : public QAbstractButton
{
public:
    VehicleButton(QAction* action, QWidget* parent = 0);

    enum VehicleType {
        TwoAxes = 0,
        ThreeAxes,
        FourAxes,
        FiveAxes,
        None
    };

    static QPixmap getVehicleIcon(const VehicleType type);
    static QPixmap getVehicleIconError(const VehicleType type);
    static QPointF getIconAxesCoordinate(const VehicleType type, const int axis);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void enterEvent(QEvent* event);
    virtual void leaveEvent(QEvent* event);

private:
    Vehicle* _vehicle = 0;
    VehicleType _vehicleType = None;

    bool _entered = false;

    static QVector<QPixmap> s_icons;
    static QVector<QPixmap> s_iconsError;
    static QVector<QVector<QPointF> > s_iconAxesCoordinates;
};

#endif
