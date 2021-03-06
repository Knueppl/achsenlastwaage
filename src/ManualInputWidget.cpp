#include "ManualInputWidget.h"
#include "ui_ManualInputWidget.h"
#include "Vehicle.h"

#include <QDebug>

ManualInputWidget::ManualInputWidget(const Vehicle* vehicle,
                                     const int goodId,
                                     const int supplierId,
                                     const int fieldId,
                                     QWidget* parnet)
    : QDialog(parnet),
      _ui(new Ui::ManualInputWidget),
      _weighting(new Weighting)
{
    _ui->setupUi(this);

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }

    switch (vehicle->axes())
    {
    case 2:
        _ui->_labelIcon->setPixmap(QPixmap(":vehicle/truck-two-axes.png"));
        break;

    case 3:
        _ui->_labelIcon->setPixmap(QPixmap(":vehicle/truck-three-axes.png"));
        break;

    case 4:
        _ui->_labelIcon->setPixmap(QPixmap(":vehicle/truck-four-axes.png"));
        break;

    case 5:
        _ui->_labelIcon->setPixmap(QPixmap(":vehicle/truck-five-axes.png"));
        break;

    default:
        qDebug() << "not inplementation for " << vehicle->axes() << " axes.";
        return;
    }

    _ui->_labelVehicle->setFont(QFont("Euro Plate", 24, QFont::Normal));
    _ui->_labelVehicle->setText(vehicle->name());

    this->connect(_ui->_buttonAdd, SIGNAL(clicked()), this, SLOT(createWeighting()));
    this->connect(_ui->_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

    // Start weighting...
    _weighting->start(vehicle, goodId, supplierId, fieldId);
}

ManualInputWidget::~ManualInputWidget(void)
{
    delete _weighting;
}

void ManualInputWidget::createWeighting(void)
{
    *_weighting << _ui->_spinBrutto->value();

    while (!_weighting->finished())
        *_weighting << 0;

    this->accept();
}
