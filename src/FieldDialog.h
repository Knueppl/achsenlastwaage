#ifndef ___FIELD_DIALOG_H___
#define ___FIELD_DIALOG_H___

#include <QWidget>

#include "Database.h"

namespace Ui {
class DatabaseCombo;
}

class FieldDialog : public QWidget
{
    Q_OBJECT

public:
    FieldDialog(QWidget* parent = 0);

    void setDatabase(Database& database);
    void getAllFieldsFromDatabase(void);

    QString selectedField(void) const;

private slots:
    void selectItem(int index);

private:
    Ui::DatabaseCombo* _ui;
    Database* _database;
};

#endif
