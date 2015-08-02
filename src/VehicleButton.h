#ifndef ___VEHICLE_BUTTON_H___
#define ___VEHICLE_BUTTON_H___

#include <QAbstractButton>
#include <QVector>

class QAction;
class Vehicle;

class VehicleButton : public QAbstractButton
{
public:
    VehicleButton(QAction* action, QWidget* parent = 0);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void enterEvent(QEvent* event);
    virtual void leaveEvent(QEvent* event);

private:
    enum VehicleType {
        TwoAxes = 0,
        ThreeAxes,
        FourAxes,
        FiveAxes,
        None
    };

    Vehicle* _vehicle = 0;
    VehicleType _vehicleType = None;

    bool _entered = false;

    static QVector<QPixmap> s_icons;
};

#endif
