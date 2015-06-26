#ifndef ___DATABASE_DIALOG_H___
#define ___DATABASE_DIALOG_H___

#include <QDialog>

#include "Database.h"

namespace Ui {
class DatabaseDialog;
}

class DatabaseDialog : public QDialog
{
    Q_OBJECT

public:
    DatabaseDialog(Database& database, QWidget* parent = 0);

private slots:
    void chooseDatabase(void);

private:
    void showDatabases(void);

    Ui::DatabaseDialog* _ui;
    Database& _database;
};

#endif
