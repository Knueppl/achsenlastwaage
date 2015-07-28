#ifndef ___VEHICLE_STACK_WIDGET_H___
#define ___VEHICLE_STACK_WIDGET_H___

#include <QWidget>
#include <QVBoxLayout>
#include <QAction>

class VehicleStackWidget : public QWidget
{
public:
    VehicleStackWidget(QWidget* parent = 0);

    void addVehicle(QAction* action);
    void clear(void);

private:
    QVBoxLayout* _layout;
};

#endif
