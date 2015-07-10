#include "CreateTextDialog.h"
#include "ui_CreateTextDialog.h"

CreateTextDialog::CreateTextDialog(QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::CreateTextDialog)
{
    _ui->setupUi(this);
    _ui->_pushAccept->setDefault(true);

    this->connect(_ui->_pushAccept, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(_ui->_pushCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

QString CreateTextDialog::databaseName(void) const
{
    return _ui->_lineName->text();
}
