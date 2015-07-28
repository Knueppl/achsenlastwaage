#ifndef ___VEHICLE_BUTTON_H___
#define ___VEHICLE_BUTTON_H___

#include <QAbstractButton>
#include <QVector>

class QAction;

class VehicleButton : public QAbstractButton
{
public:
    VehicleButton(QAction* action, QWidget* parent = 0);

protected:
    virtual void paintEvent(QPaintEvent* event);

private:
    enum VehicleType {
        TwoAxes = 0,
        ThreeAxes,
        FourAxes,
        FiveAxes
    };

    VehicleType _vehicleType;

    static QVector<QPixmap> s_icons;
};

#endif
