#include "WeightingScene.h"
#include "Vehicle.h"

#include <QGraphicsPixmapItem>
#include <QTextDocument>
#include <QTextOption>
#include <QDebug>

WeightingScene::WeightingScene(QObject* parent)
    : QGraphicsScene(parent),
      _vehicleItem(0),
      _axisWeightItem(0),
      _vehicleNameItem(0),
      _axesWeightsItem(0),
      _axesLabelItem(0),
      _weightsItem(0),
      _weightsLabelItem(0),
      _vehicle(0),
      _currentAxis(-1),
      _showError(false)
{
    QPen pen;
    QBrush brush(Qt::black);

    pen.setWidth(1);
    this->addLine(-13, 0, -250, 0, pen);
    this->addLine( 13, 0,  250, 0, pen);
    this->addRect(-9, 0, 18, 4, Qt::NoPen, brush);

    _axisWeightItem = this->addText(QString(""), QFont("Times", 16, QFont::Normal));
    _axisWeightItem->setTextWidth(128);
    _axisWeightItem->setPos(-_axisWeightItem->textWidth() * 0.5f, 3);

    _vehicleNameItem = this->addSimpleText(QString(""), QFont("Euro Plate", 24, QFont::Normal));
    _vehicleNameItem->setPos(-250, -108);

    _axesWeightsItem = this->addText(QString(""), QFont("Times", 12, QFont::Normal));
    _axesWeightsItem->setTextWidth(80);
    _axesWeightsItem->setPos(250 - 80, -116);
    _axesWeightsItem->document()->setDefaultTextOption(QTextOption(Qt::AlignRight));

    _axesLabelItem = this->addText(QString(""), QFont("Times", 12, QFont::Normal));
    _axesLabelItem->setTextWidth(80);
    _axesLabelItem->setPos(250 - 160, -116);
    _axesLabelItem->document()->setDefaultTextOption(QTextOption(Qt::AlignRight));

    _weightsItem = this->addText(QString(""), QFont("Times", 12, QFont::Normal));
    _weightsItem->setTextWidth(80);
    _weightsItem->setPos(250 - 80, 3);
    _weightsItem->document()->setDefaultTextOption(QTextOption(Qt::AlignRight));

    _weightsLabelItem = this->addText(QString(""), QFont("Times", 12, QFont::Normal));
    _weightsLabelItem->setTextWidth(80);
    _weightsLabelItem->setPos(250 - 160, 3);
    _weightsLabelItem->document()->setDefaultTextOption(QTextOption(Qt::AlignRight));

    this->connect(&_timer, SIGNAL(timeout()), this, SLOT(tick()));
}

WeightingScene::~WeightingScene(void)
{

}

void WeightingScene::start(const Vehicle* vehicle)
{
    if (_vehicleItem)
    {
        this->removeItem(_vehicleItem);
        delete _vehicleItem;
    }

    _vehicleType = static_cast<VehicleButton::VehicleType>(vehicle->axes() - 2);
    _vehicleItem = this->addPixmap(VehicleButton::getVehicleIcon(_vehicleType));
    _vehicleItem->setPos(30, -_vehicleItem->pixmap().height() - 4);

    _vehicleNameItem->setText(vehicle->name());
    _axesWeightsItem->setPlainText("");
    _axesLabelItem->setPlainText("");

    _weightsItem->setPlainText(QString("0 kg\n") + QString::number(vehicle->tara()) + QString(" kg\n0 kg"));
    _weightsLabelItem->setPlainText("Brutto:\nTARA:\nNetto:");

    _vehicle = vehicle;
    _currentAxis = 1;
    _sum = 0;
    _timer.start(50);
}

void WeightingScene::setNextWeight(const int kg)
{
    QTextDocument* document = _axisWeightItem->document();

    document->setPlainText(QString::number(kg) + QString(" kg"));
    document->setDefaultTextOption(QTextOption(Qt::AlignHCenter));
    _axisWeightItem->setPos(-_axisWeightItem->textWidth() * 0.5f, 3);

    _axesWeightsItem->setPlainText(_axesWeightsItem->toPlainText() + QString::number(kg) + QString(" kg\n"));
    _axesLabelItem->setPlainText(_axesLabelItem->toPlainText() +
                                 QString("Achse ") +
                                 QString::number(_currentAxis) +
                                 QString(":\n"));

    _sum += kg;
    _weightsItem->setPlainText(QString::number(_sum) + QString(" kg\n") +
                               QString::number(_vehicle->tara()) + QString(" kg\n") +
                               QString::number(_sum - _vehicle->tara()) + QString(" kg"));

    if (++_currentAxis > _vehicleType + 2)
        _currentAxis = _vehicleType + 2;

    _timer.start(50);
}

void WeightingScene::tick(void)
{
    const QPointF vehiclePos(VehicleButton::getIconAxesCoordinate(_vehicleType, _currentAxis - 1));

    if (_vehicleItem->pos().x() <= -vehiclePos.x())
    {
        _timer.stop();
        return;
    }

    _vehicleItem->moveBy(-1, 0);
}

void WeightingScene::showError(void)
{
    _vehicleItem = this->addPixmap(VehicleButton::getVehicleIconError(_vehicleType));
}
