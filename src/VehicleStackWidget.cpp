#include "VehicleStackWidget.h"
#include "VehicleButton.h"
#include "Vehicle.h"

#include <QDebug>

VehicleStackWidget::VehicleStackWidget(QWidget* parent)
    : QWidget(parent),
      _layout(new QVBoxLayout)
{
    this->setLayout(_layout);
}

void VehicleStackWidget::addVehicle(QAction* action)
{
    if (!action)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !action --> return";
        return;
    }

    Vehicle* vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }

    VehicleButton* button = new VehicleButton(action);
    button->show();
    _layout->insertWidget(0, button);
//    this->setLayout(_layout);
    this->show();
}

void VehicleStackWidget::clear(void)
{
    QLayoutItem *child;

    while ((child = _layout->takeAt(0)))
        delete child;
}
