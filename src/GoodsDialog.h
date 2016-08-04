#ifndef ___GOODS_DIALOG_H___
#define ___GOODS_DIALOG_H___

#include <QWidget>
#include <QString>

#include "Database.h"

namespace Ui {
class DatabaseCombo;
}

class GoodsDialog : public QWidget
{
    Q_OBJECT

public:
    GoodsDialog(QWidget* parent = 0);
    GoodsDialog(Database& database, QWidget* parent = 0);

    void setDatabase(Database& database);
    void getAllGoodsFromDatabase(void);

    QString selectedGood(void) const;
    int selectedId(void) const;

private slots:
    void selectItem(int index);

private:
    Ui::DatabaseCombo* _ui;
    Database* _database;
};

#endif
