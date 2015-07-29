#include "VehicleButton.h"
#include "Vehicle.h"

#include <QAction>
#include <QPainter>
#include <QDebug>
#include <QEvent>

QVector<QPixmap> VehicleButton::s_icons;

VehicleButton::VehicleButton(QAction* action, QWidget* parent)
    : QAbstractButton(parent)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!s_icons.size())
    {
        s_icons.push_back(QPixmap(":vehicle/truck-two-axes.png"));
        s_icons.push_back(QPixmap(":vehicle/truck-three-axes.png"));
        s_icons.push_back(QPixmap(":vehicle/truck-four-axes.png"));
        s_icons.push_back(QPixmap(":vehicle/truck-five-axes.png"));
    }

    Vehicle* vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }

    _vehicleType = static_cast<VehicleType>(vehicle->axes() - 2);

    this->setMinimumHeight(42);
}

void VehicleButton::paintEvent(QPaintEvent*)
{
    qDebug() << __PRETTY_FUNCTION__;
    QPainter painter(this);

    painter.drawPixmap(QRect(this->width() >> 1,
                             0,
                             (this->width() >> 1) + s_icons[_vehicleType].width(),
                             s_icons[_vehicleType].height()),
                       s_icons[_vehicleType],
                       s_icons[_vehicleType].rect());
}

void VehicleButton::enterEvent(QEvent* event)
{
    event->accept();
    qDebug() << __PRETTY_FUNCTION__;
}
