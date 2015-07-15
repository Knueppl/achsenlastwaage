#include "GoodsDialog.h"
#include "ui_DatabaseCombo.h"
#include "CreateTextDialog.h"

GoodsDialog::GoodsDialog(QWidget* parent)
    : QWidget(),
      _ui(new Ui::DatabaseCombo),
      _database(0)
{
    _ui->setupUi(this);
}

GoodsDialog::GoodsDialog(Database& database, QWidget* parent)
    : QWidget(),
      _ui(new Ui::DatabaseCombo),
      _database(&database)
{
    _ui->setupUi(this);
}

void GoodsDialog::setDatabase(Database& database)
{
    _database = &database;
    this->getAllGoodsFromDatabase();
}

QString GoodsDialog::selectedGood(void) const
{
    return _ui->_combo->currentText();
}

void GoodsDialog::selectItem(int index)
{
    if (index < 0)
        return;

    if (index == _ui->_combo->count() - 1)
    {
        CreateTextDialog dialog(this);

        if (dialog.exec() == QDialog::Accepted)
        {
            if (dialog.text().isEmpty())
                return;

            _database->addGood(dialog.text());
            this->getAllGoodsFromDatabase();
        }
    }
}

void GoodsDialog::getAllGoodsFromDatabase(void)
{
    QVector<QString> goods;

    _database->getAllGoods(goods);
    this->disconnect(_ui->_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem(int)));
    _ui->_combo->clear();

    foreach (const QString& good, goods)
        _ui->_combo->addItem(good);

    _ui->_combo->addItem("Erstelle neue Ware");
    _ui->_combo->setCurrentIndex(0);
    this->connect(_ui->_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(selectItem(int)));
}
