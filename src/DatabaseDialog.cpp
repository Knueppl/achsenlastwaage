#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"
#include "CreateTextDialog.h"

#include <QDebug>

DatabaseDialog::DatabaseDialog(Database& database, QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::DatabaseDialog),
      _database(database)
{
    _ui->setupUi(this);

    _ui->_pushAccept->setDefault(true);
    this->showDatabases();
    this->connect(_ui->_pushAccept, SIGNAL(clicked()), this, SLOT(accept()));
    this->connect(_ui->_comboDatabases, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseDatabase(int)));
    this->connect(_ui->_pushCancel, SIGNAL(clicked()), this, SLOT(reject()));

    // If their is no valid database, create one without the choose database dialog.
    if (_ui->_comboDatabases->count() == 1)
    {
        _database.selectDatabase("information_schema");
        this->chooseDatabase(0);
    }
}

void DatabaseDialog::chooseDatabase(int index)
{
    if (index < 0)
        return;

    if (index == _ui->_comboDatabases->count() - 1)
    {
        CreateTextDialog dialog(this);

        if (dialog.exec() == QDialog::Accepted)
        {
            if (dialog.text().isEmpty())
                return;

            qDebug() << "create database: " << dialog.text();
            _database.createDatabase(dialog.text());
            this->showDatabases();
            _database.selectDatabase(_ui->_comboDatabases->currentText());
            this->accept();
        }

        return;
    }

    _database.selectDatabase(_ui->_comboDatabases->currentText());
    this->accept();
}

void DatabaseDialog::showDatabases(void)
{
    this->disconnect(_ui->_comboDatabases, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseDatabase(int)));
    _ui->_comboDatabases->clear();

    _database.selectDatabase("information_schema");
    QVector<QString> databases(_database.databases());

    for (QVector<QString>::const_iterator it(databases.begin()); it < databases.end(); ++it)
        _ui->_comboDatabases->addItem(*it);

    _ui->_comboDatabases->addItem("Erstelle neue Datenbank");
    _ui->_comboDatabases->setCurrentIndex(0);
    this->connect(_ui->_comboDatabases, SIGNAL(currentIndexChanged(int)), this, SLOT(chooseDatabase(int)));
}
