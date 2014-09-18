#include "CreateVehicleDialog.h"
#include "ui_CreateVehicleDialog.h"

CreateVehicleDialog::CreateVehicleDialog(QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::CreateVehicleDialog),
      _vehicle(0)
{
    _ui->setupUi(this);

    connect(_ui->_buttonAdd, SIGNAL(clicked()), this, SLOT(createVehicle()));
    connect(_ui->_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void CreateVehicleDialog::createVehicle(void)
{
    _vehicle = new Vehicle;

    _vehicle->_name = _ui->_editName->text();
    _vehicle->_numberOfAxis = _ui->_spinAxes->value();
    _vehicle->_tara = _ui->_spinTara->value();

    this->accept();
}
