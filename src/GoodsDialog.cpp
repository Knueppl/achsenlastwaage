#include "GoodsDialog.h"
#include "ui_GoodsDialog.h"

GoodsDialog::GoodsDialog(Database& database, QWidget* parent)
    : QWidget(),
      _ui(new Ui::GoodsDialog),
      _database(database)
{
    _ui->setupUi(this);
}

const QString& GoodsDialog::selectedGood(void) const
{
    _ui->_comboGoods->currentText();
}

