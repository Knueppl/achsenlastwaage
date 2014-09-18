#ifndef ___CREATE_VEHICLE_DIALOG_H___
#define ___CREATE_VEHICLE_DIALOG_H___

#include <QDialog>

#include "Vehicle.h"

namespace Ui {
class CreateVehicleDialog;
}

class CreateVehicleDialog : public QDialog
{
    Q_OBJECT;

public:
    CreateVehicleDialog(QWidget* parent = 0);

private slots:
    void createVehicle(void);

private:
    Ui::CreateVehicleDialog* _ui;
    Vehicle* _vehicle;
};

#endif
