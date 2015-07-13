#include "GoodsDialog.h"
#include "ui_GoodsDialog.h"

GoodsDialog::GoodsDialog(Database& database, QWidget* parent)
    : QWidget(),
      _ui(new Ui::GoodsDialog),
      _database(0)
{
    _ui->setupUi(this);
}

GoodsDialog::GoodsDialog(Database& database, QWidget* parent)
    : QWidget(),
      _ui(new Ui::GoodsDialog),
      _database(&database)
{
    _ui->setupUi(this);
}

const QString& GoodsDialog::selectedGood(void) const
{
    _ui->_comboGoods->currentText();
}

void GoodsDialog::selectItem(int index)
{
    if (index < 0)
        return;

    if (index == _ui->_comboGoods->count() - 1)
    {
        // TO DO: text dialog...
    }
}

void GoodsDialog::getAllGoodsFromDatabase(void)
{
    QVector<QString> goods;

    _database->getAllGoods(goods);
    this->disconnect(_ui->_comboGoods, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem(int)));
    _ui->_comboGoods->clear();

    for (auto good : goods)
        _ui->_comboGoods->addItem(good);

    _ui->_comboGoods->addItem("Erstelle neue Ware");
    this->connect(_ui->_comboGoods, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem(int)));
}
