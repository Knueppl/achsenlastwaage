#ifndef ___SUPPLIER_DIALOG_H___
#define ___SUPPLIER_DIALOG_H___

#include <QWidget>

#include "Database.h"

namespace Ui {
class DatabaseCombo;
}

class SupplierDialog : public QWidget
{
    Q_OBJECT

public:
    SupplierDialog(QWidget* parent = 0);

    void setDatabase(Database& database);
    void getAllSuppliersFromDatabase(void);

    QString selectedSupplier(void) const;

private slots:
    void selectItem(int index);

private:
    Ui::DatabaseCombo* _ui;
    Database* _database;
};

#endif
