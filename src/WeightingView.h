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

    void setDatabase(Database& database);

public slots:
    void getAllWeightings(void);

private:
    void getSuppliers(const int fieldId, const int goodId, const int vehicleId);
    void getFields(const int supplierId, const int goodId, const int vehicleId);
    void getGoods(const int supplierId, const int fieldId, const int vehicleId);
    void getVehicles(const int supplierId, const int fieldId, const int goodId);

    Ui::WeightingView* _ui;
    Database* _database;
};

#endif
