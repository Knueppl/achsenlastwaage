#include "VehicleStackWidget.h"
#include "VehicleButton.h"
#include "Vehicle.h"

#include <QDebug>
#include <QEvent>

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

    _layout->addWidget(new VehicleButton(action));
}

void VehicleStackWidget::addVehicles(QVector<QAction*> actions)
{
    QVector<VehicleButton*> buttons;

    for (auto action : actions)
        buttons.push_back(new VehicleButton(action));


    QVBoxLayout* layout = new QVBoxLayout;

    for (auto button : buttons)
        layout->addWidget(button);

    this->setLayout(layout);
}

void VehicleStackWidget::clear(void)
{
    QLayoutItem *child;

    while ((child = _layout->takeAt(0)))
        delete child;

    delete this->layout();
}

void VehicleStackWidget::enterEvent(QEvent* event)
{
    event->accept();
    qDebug() << __PRETTY_FUNCTION__;
}
