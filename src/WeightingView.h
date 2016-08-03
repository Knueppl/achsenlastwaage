#ifndef ___WEIGHTING_VIEW_H___
#define ___WEIGHTING_VIEW_H___

#include <QWidget>

#include "Database.h"

namespace Ui {
class WeightingView;
}

class WeightingView : public QWidget
{
    Q_OBJECT

public:
    explicit WeightingView(QWidget* parent = 0);

    void setDatabase(Database& database) { _database = &database; }

public slots:
    void getAllWeightings(void);

private:
    Ui::WeightingView* _ui;
    Database* _database;
};

#endif
