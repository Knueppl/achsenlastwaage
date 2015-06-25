#include "DatabaseDialog.h"
#include "ui_DatabaseDialog.h"

DatabaseDialog::DatabaseDialog(Database& database, QWidget* parent)
    : QDialog(parent),
      _ui(new Ui::DatabaseDialog),
      _database(database)
{
    _ui->setupUi(this);

    database.connect("information_schema");
    QVector<QString> databases(database.databases());

    for (QVector<QString>::const_iterator it(databases.begin()); it < databases.end(); ++it)
        _ui->_comboDatabases->addItem(*it);
}

void DatabaseDialog::chooseDatabase(void)
{
    _database.connect(_ui->_comboDatabases->currentText());
}
