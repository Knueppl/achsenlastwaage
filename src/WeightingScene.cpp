#include "WeightingScene.h"

#include <QGraphicsPixmapItem>
#include <QDebug>

WeightingScene::WeightingScene(QObject* parent)
    : QGraphicsScene(parent),
      _vehicle(0),
      _currentAxis(-1)
{
    QPen pen;
    QBrush brush(Qt::black);

    pen.setWidth(1);
    this->addLine(-13, 0, -250, 0, pen);
    this->addLine( 13, 0,  250, 0, pen);
    this->addRect(-9, 0, 18, 4, Qt::NoPen, brush);

    this->connect(&_timer, SIGNAL(timeout()), this, SLOT(tick()));
}

WeightingScene::~WeightingScene(void)
{

}

void WeightingScene::start(const int axes)
{
    if (_vehicle)
    {
        this->removeItem(_vehicle);
        delete _vehicle;
    }

    _vehicleType = static_cast<VehicleButton::VehicleType>(axes - 2);
    _vehicle = this->addPixmap(VehicleButton::getVehicleIcon(_vehicleType));
    _vehicle->setPos(30, -_vehicle->pixmap().height() - 4);
    _currentAxis = 1;
    _timer.start(50);
}

void WeightingScene::setNextWeight(const int kg)
{

}

void WeightingScene::tick(void)
{
    const QPointF vehiclePos(VehicleButton::getIconAxesCoordinate(_vehicleType, _currentAxis - 1));

    if (_vehicle->pos().x() <= -vehiclePos.x())
    {
        _timer.stop();
        return;
    }

    _vehicle->moveBy(-1, 0);
}
