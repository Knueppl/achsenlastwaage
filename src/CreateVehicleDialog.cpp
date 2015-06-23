#include "CreateVehicleDialog.h"
#include "ui_CreateVehicleDialog.h"

#include <QMessageBox>

CreateVehicleDialog::CreateVehicleDialog(QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::CreateVehicleDialog),
      _vehicle(0)
{
    _ui->setupUi(this);

    this->connect(_ui->_buttonAdd, SIGNAL(clicked()), this, SLOT(createVehicle()));
    this->connect(_ui->_buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void CreateVehicleDialog::createVehicle(void)
{
    if (_ui->_editName->text().isEmpty())
    {
        QMessageBox msg(this);
        msg.setText("Fahrzeugname darf nicht leer sein.");
        msg.exec();

        return;
    }
    if (_ui->_spinTara->value() <= 0)
    {
        QMessageBox msg(this);
        msg.setText("Die TARA muss größer null sein.");
        msg.exec();

        return;
    }

    _vehicle = new Vehicle(_ui->_editName->text(), _ui->_spinAxes->value(), _ui->_spinTara->value());
    this->accept();
}
