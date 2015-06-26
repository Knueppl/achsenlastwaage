#include "CreateDatabaseDialog.h"
#include "ui_CreateDatabaseDialog.h"

CreateDatabaseDialog::CreateDatabaseDialog(QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::CreateDatabaseDialog)
{
    _ui->setupUi(this);
    _ui->_pushAccept->setDefault(true);

    this->connect(_ui->_pushAccept, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(_ui->_pushCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QString CreateDatabaseDialog::databaseName(void) const
{
    return _ui->_lineName->text();
}
