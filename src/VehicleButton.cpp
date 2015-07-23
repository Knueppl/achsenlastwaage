#include "VehicleButton.h"
#include "Vehicle.h"

#include <QPainter>
#include <QDebug>

QVector<QPixmap> VehicleButton::s_icons = { QPixmap(":vehicle/truck-two-axes.png"),
                                            QPixmap(":vehicle/truck-three-axes.png"),
                                            QPixmap(":vehicle/truck-four-axes.png"),
                                            QPixmap(":vehicle/truck-five-axes.png") };

VehicleButton::VehicleButton(Vehicle* vehicle, QWidget* parent)
    : QAbstractButton(parent)
{
    Vehicle* vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }

    _vehicleType = vehicle->axes() - 2;
}

void VehicleButton::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.drawPixmap(QRect(this->width() >> 1,
                             0,
                             (this->width() >> 1) + s_icons[_vehicleType].width(),
                             s_icons[_vehicleType].height()),
                       s_icons[_vehicleType],
                       s_icons[_vehicleType].rect());
}
