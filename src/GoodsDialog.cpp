#include "GoodsDialog.h"
#include "ui_DatabaseCombo.h"
#include "CreateTextDialog.h"

GoodsDialog::GoodsDialog(QWidget* parent)
    : QWidget(),
      _ui(new Ui::DatabaseCombo),
      _database(0)
{
    _ui->setupUi(this);
    this->setDisabled(true);
}

GoodsDialog::GoodsDialog(Database& database, QWidget* parent)
    : QWidget(),
      _ui(new Ui::DatabaseCombo),
      _database(&database)
{
    _ui->setupUi(this);
    this->setDisabled(true);
}

void GoodsDialog::setDatabase(Database& database)
{
    _database = &database;
}

QString GoodsDialog::selectedGood(void) const
{
    if (_ui->_combo->currentIndex() == _ui->_combo->count() - 1)
        return QString("");

    return _ui->_combo->currentText();
}

int GoodsDialog::selectedId(void) const
{
    if (_ui->_combo->currentIndex() == _ui->_combo->count() - 1)
        return 0;

    return _ui->_combo->currentIndex() + 1;
}

void GoodsDialog::selectItem(int index)
{
    if (index < 0)
        return;

    if (index == _ui->_combo->count() - 1)
    {
        CreateTextDialog dialog(this);

        dialog.setInfoText("Geben Sie bitte den Namen der neuen Ware ein.");

        if (dialog.exec() == QDialog::Accepted)
        {
            if (dialog.text().isEmpty())
            {
                _ui->_combo->setCurrentIndex(0);
                return;
            }

            _database->addGood(dialog.text());
            this->getAllGoodsFromDatabase();
        }

        _ui->_combo->setCurrentIndex(0);
    }
}

void GoodsDialog::getAllGoodsFromDatabase(void)
{
    QVector<QString> goods;

    _database->getAllGoods(goods);
    this->disconnect(_ui->_combo, SIGNAL(activated(int)), this, SLOT(selectItem(int)));
    _ui->_combo->clear();

    foreach (const QString& good, goods)
        _ui->_combo->addItem(good);

    _ui->_combo->addItem("Erstelle neue Ware");
    _ui->_combo->setCurrentIndex(0);
    this->setEnabled(true);
    this->connect(_ui->_combo, SIGNAL(activated(int)), this, SLOT(selectItem(int)));
}
