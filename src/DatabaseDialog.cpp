#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"
#include "CreateDatabaseDialog.h"

DatabaseDialog::DatabaseDialog(Database& database, QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::DatabaseDialog),
      _database(database)
{
    _ui->setupUi(this);

    _ui->_pushAccept->setDefault(true);
    this->connect(_ui->_pushAccept, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(_ui->_pushAccept, SIGNAL(clicked()), this, SLOT(chooseDatabase()));
    this->connect(_ui->_pushCancel, SIGNAL(clicked()), this, SLOT(reject()));
    this->showDatabases();
}

void DatabaseDialog::chooseDatabase(void)
{
    if (!_ui->_comboDatabases->currentIndex())
    {
        CreateDatabaseDialog dialog(this);

        if (dialog.exec() == QDialog::Accepted)
        {
            if (dialog.databaseName().isEmpty())
                return;

            _database.createDatabase(dialog.databaseName());
            this->showDatabases();
            _ui->_comboDatabases->setCurrentIndex(_ui->_comboDatabases->count());
            _database.selectDatabase(_ui->_comboDatabases->currentText());
        }

        return;
    }

    _database.selectDatabase(_ui->_comboDatabases->currentText());
}

void DatabaseDialog::showDatabases(void)
{
    _ui->_comboDatabases->clear();
    _ui->_comboDatabases->addItem("Erstelle neue Datenbank");

    _database.selectDatabase("information_schema");
    QVector<QString> databases(_database.databases());

    for (QVector<QString>::const_iterator it(databases.begin()); it < databases.end(); ++it)
        _ui->_comboDatabases->addItem(*it);
}
