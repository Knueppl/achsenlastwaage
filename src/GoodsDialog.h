#ifndef ___GOODS_DIALOG_H___
#define ___GOODS_DIALOG_H___

#include <QWidget>
#include <QString>

#include "Database.h"

namespace Ui {
class GoodsDialog;
}

class GoodsDialog : public QWidget
{
    Q_OBJECT

public:
    GoodsDialog(QWidget* parent = 0);
    GoodsDialog(Database& database, QWidget* parent = 0);

    void setDatabase(Database& database) { _database = &database; }

    const QString& selectedGood(void) const;

private slots:
    void selectItem(int index);

private:
    void getAllGoodsFromDatabase(void);

    Ui::GoodsDialog* _ui;
    Database* _database;
};

#endif
