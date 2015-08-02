#include "ScaleWidget.h"
#include "WeightingScene.h"
#include "Vehicle.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QDebug>

ScaleWidget::ScaleWidget(QWidget* parent)
    : QWidget(parent),
      _scene(new WeightingScene),
      _view(new QGraphicsView(_scene))
{
    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(_view);
    this->setLayout(layout);
}

void ScaleWidget::start(void)
{
    // Check if the sender is an action.
    QAction* action = qobject_cast<QAction*>(this->sender());

    if (!action)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !action --> return";
        return;
    }


    // Then check if the action has as value a vehicle.
    Vehicle* vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }


    _scene->start(vehicle->axes());
}

void ScaleWidget::showAxisWeight(const int kg)
{
    _scene->setNextWeight(kg);
}
