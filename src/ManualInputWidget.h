#ifndef ___MANUAL_INPUT_WIDGET_H___
#define ___MANUAL_INPUT_WIDGET_H___

#include <QDialog>

class Vehicle;

namespace Ui {
class ManualInputWidget;
}

class ManualInputWidget : public QDialog
{
public:
    explicit ManualInputWidget(const Vehicle* vehicle, QWidget* parnet = 0);

private:
    Ui::ManualInputWidget* _ui;
};

#endif
