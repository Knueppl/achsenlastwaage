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
    void filterHasBeenChanged(int index);

private:
    void getSuppliers(const QString& field = QString(),
		      const QString& good = QString(),
		      const QString& vehicle = QString());
    void getFields(const QString& supplier = QString(),
		   const QString& good = QString(),
		   const QString& vehicle = QString());
    void getGoods(const QString& supplier = QString(),
		  const QString& field = QString(),
		  const QString& vehicle = QString());
    void getVehicles(const QString& supplier = QString(),
		     const QString& field = QString(),
		     const QString& good = QString());

    Ui::WeightingView* _ui;
    Database* _database;
};

#endif
