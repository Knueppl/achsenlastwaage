#ifndef ___VEHICLE_STACK_WIDGET_H___
#define ___VEHICLE_STACK_WIDGET_H___

#include <QWidget>
#include <QVBoxLayout>
#include <QAction>
#include <QVector>

class VehicleStackWidget : public QWidget
{
public:
    VehicleStackWidget(QWidget* parent = 0);

    void addVehicle(QAction* action);
    void addVehicles(QVector<QAction*> actions);
    void clear(void);

protected:
    virtual void enterEvent(QEvent* event);

private:
    QVBoxLayout* _layout;
};

#endif
