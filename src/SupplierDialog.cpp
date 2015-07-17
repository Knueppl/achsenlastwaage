#include "SupplierDialog.h"
#include "ui_DatabaseCombo.h"
#include "CreateTextDialog.h"

SupplierDialog::SupplierDialog(QWidget* parent)
    : QWidget(parent),
      _ui(new Ui::DatabaseCombo),
      _database(0)
{
    _ui->setupUi(this);
}

void SupplierDialog::setDatabase(Database& database)
{
    _database = &database;
}

QString SupplierDialog::selectedSupplier(void) const
{
    if (_ui->_combo->currentIndex() == _ui->_combo->count() - 1)
        return QString("");

    return _ui->_combo->currentText();
}

void SupplierDialog::selectItem(int index)
{
    if (index < 0)
        return;

    if (index == _ui->_combo->count() - 1)
    {
        CreateTextDialog dialog(this);

        dialog.setInfoText("Geben Sie bitte den Namen des Lieferanten ein.");

        if (dialog.exec() == QDialog::Accepted)
        {
            if (dialog.text().isEmpty())
            {
                _ui->_combo->setCurrentIndex(0);
                return;
            }

            _database->addSupplier(dialog.text());
            this->getAllSuppliersFromDatabase();
        }

        _ui->_combo->setCurrentIndex(0);
    }
}

void SupplierDialog::getAllSuppliersFromDatabase(void)
{
    QVector<QString> suppliers;

    _database->getAllSuppliers(suppliers);
    this->disconnect(_ui->_combo, SIGNAL(activated(int)), this, SLOT(selectItem(int)));
    _ui->_combo->clear();

    foreach (const QString& supplier, suppliers)
        _ui->_combo->addItem(supplier);

    _ui->_combo->addItem("Erstelle neuen Lieferanten");
    _ui->_combo->setCurrentIndex(0);
    this->connect(_ui->_combo, SIGNAL(activated(int)), this, SLOT(selectItem(int)));
}
