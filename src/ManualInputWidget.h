#ifndef ___MANUAL_INPUT_WIDGET_H___
#define ___MANUAL_INPUT_WIDGET_H___

#include <QDialog>

class Vehicle;

#include "Weighting.h"

namespace Ui {
class ManualInputWidget;
}

class ManualInputWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ManualInputWidget(const Vehicle* vehicle,
                               const int goodId,
                               const int supplierId,
                               const int fieldId,
                               QWidget* parnet = 0);
    ~ManualInputWidget(void);
    const Weighting* getWeighting(void) const { return _weighting; }

private slots:
    void createWeighting(void);

private:
    Ui::ManualInputWidget* _ui;
    Weighting* _weighting;
};

#endif
