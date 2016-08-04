#include "FieldDialog.h"
#include "ui_DatabaseCombo.h"
#include "CreateTextDialog.h"

FieldDialog::FieldDialog(QWidget* parent)
    : QWidget(parent),
      _ui(new Ui::DatabaseCombo),
      _database(0)
{
    _ui->setupUi(this);
    this->setDisabled(true);
}

void FieldDialog::setDatabase(Database& database)
{
    _database = &database;
}

QString FieldDialog::selectedField(void) const
{
    if (_ui->_combo->currentIndex() == _ui->_combo->count() - 1)
        return QString("");

    return _ui->_combo->currentText();
}

int FieldDialog::selectedId(void) const
{
    if (_ui->_combo->currentIndex() == _ui->_combo->count() - 1)
        return 0;

    return _ui->_combo->currentIndex() + 1;
}

void FieldDialog::selectItem(int index)
{
    if (index < 0)
        return;

    if (index == _ui->_combo->count() - 1)
    {
        CreateTextDialog dialog(this);

        dialog.setInfoText("Geben Sie bitte den Namen des Feldes ein.");

        if (dialog.exec() == QDialog::Accepted)
        {
            if (dialog.text().isEmpty())
            {
                _ui->_combo->setCurrentIndex(0);
                return;
            }

            _database->addField(dialog.text());
            this->getAllFieldsFromDatabase();
        }

        _ui->_combo->setCurrentIndex(0);
    }
}

void FieldDialog::getAllFieldsFromDatabase(void)
{
    QVector<QString> fields;

    _database->getAllFields(fields);
    this->disconnect(_ui->_combo, SIGNAL(activated(int)), this, SLOT(selectItem(int)));
    _ui->_combo->clear();

    foreach (const QString& field, fields)
        _ui->_combo->addItem(field);

    _ui->_combo->addItem("Füge Feld hinzu");
    _ui->_combo->setCurrentIndex(0);
    this->setEnabled(true);
    this->connect(_ui->_combo, SIGNAL(activated(int)), this, SLOT(selectItem(int)));
}
