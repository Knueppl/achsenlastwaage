#ifndef ___CREATE_DATABASE_DIALOG_H___
#define ___CREATE_DATABASE_DIALOG_H___

namespace Ui {
class CreateDatabaseDialog;
}

#include <QDialog>
#include <QString>

class CreateDatabaseDialog : public QDialog
{
public:
    CreateDatabaseDialog(QWidget* parent = 0);

    QString databaseName(void) const;

private:
    Ui::CreateDatabaseDialog* _ui;
};

#endif
