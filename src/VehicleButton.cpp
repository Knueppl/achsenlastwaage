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
    // Initialize pixmaps once.
    if (!s_icons.size())
    {
        s_icons.push_back(QPixmap(":vehicle/truck-two-axes.png"));
        s_icons.push_back(QPixmap(":vehicle/truck-three-axes.png"));
        s_icons.push_back(QPixmap(":vehicle/truck-four-axes.png"));
        s_icons.push_back(QPixmap(":vehicle/truck-five-axes.png"));
    }


    // Try to get the vehicle from the given action.
    _vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!_vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }


    // Estimate the vehicle type.
    _vehicleType = static_cast<VehicleType>(_vehicle->axes() - 2);

    if (_vehicleType < TwoAxes || _vehicleType > FiveAxes)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": _vehicleType is not valid --> set to 0";
        _vehicleType = None;
    }


    // Set size parameters.
    this->setMinimumHeight(s_icons[0].height());
    // Connect this button to the action.
    this->connect(this, SIGNAL(clicked()), action, SLOT(trigger()));
}

void VehicleButton::paintEvent(QPaintEvent*)
{
    qDebug() << __PRETTY_FUNCTION__;
    if (!_vehicle)
        return;

    QPainter painter(this);

    painter.drawLine(0, this->height() - 1, this->width() - 1, this->height() - 1);
    painter.setFont(QFont("Euro Plate", 24, QFont::Normal));
    painter.drawText(QPoint(0, 24), _vehicle->name());
    painter.setFont(QFont("Times", 12, QFont::Normal));
    painter.drawText(QPoint(0, this->height() - 7),
                     QString("TARA: ") + QString::number(_vehicle->tara()) + QString(" kg"));

    if (_vehicleType != None)
    {
        painter.drawPixmap(QRect(this->width() >> 1,
                                 0,
                                 s_icons[_vehicleType].width(),
                                 s_icons[_vehicleType].height()),
                           s_icons[_vehicleType],
                           s_icons[_vehicleType].rect());
    }
    if (this->isDown())
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(0x00, 0xa0, 0xa0, 0x70), Qt::SolidPattern));
        painter.drawRect(this->rect());
    }
    else if (_entered)
    {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(QColor(0x00, 0xff, 0xff, 0x70), Qt::SolidPattern));
        painter.drawRect(this->rect());
    }
}

void VehicleButton::enterEvent(QEvent* event)
{
    event->accept();
    _entered = true;
}

void VehicleButton::leaveEvent(QEvent* event)
{
    event->accept();
    _entered = false;
}
