#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CreateVehicleDialog.h"
#include "DatabaseDialog.h"
#include "Fzw12.h"
#include "ManualInputWidget.h"

#include <QDebug>

MainWindow* MainWindow::s_instance = 0;

MainWindow* MainWindow::instance(void)
{
    if (!s_instance)
        s_instance = new MainWindow;

    return s_instance;
}

MainWindow::MainWindow(void)
    : QMainWindow(),
      _ui(new Ui::MainWindow),
      _scale(new DummyScale)
//      _scale(new Fzw12("/dev/ttyUSB0"))
{
    _ui->setupUi(this);
    _ui->_goods->setDatabase(_database);
    _ui->_suppliers->setDatabase(_database);
    _ui->_fields->setDatabase(_database);
    _ui->_weightingView->setDatabase(_database);

    /* Create menus. */
    QMenuBar* bar = this->menuBar();
    QMenu* menu = bar->addMenu("Befehl");
    _menuStartWeighting = menu->addMenu("Starte Wiegung");
    _menuManualInput = menu->addMenu("Manuelle Wiegung");
    _cancelWeighting = menu->addAction("Wiegung abbrechen", _scale, SLOT(cancel()));
    _cancelWeighting->setDisabled(true);
    menu->addAction("Fahrzeug hinzufügen", this, SLOT(addVehicle()));

    menu = bar->addMenu("Datenbank");
    menu->addAction("Auswählen", this, SLOT(selectDatabase()));


    // For debugging.
    _scaleWidget = new DummyScaleWidget(_scale);
    _scaleWidget->show();
    this->connect(_scale, SIGNAL(finished(Weighting*)), this, SLOT(stopWeighting(Weighting*)));
    this->connect(_scale, SIGNAL(axisWeight(const int)), _ui->_scale, SLOT(showAxisWeight(const int)));
}

MainWindow::~MainWindow(void)
{

}

void MainWindow::getAllVehiclesFromDatabase(void)
{
    qDeleteAll(_vehicles);
    _vehicles.clear();
    _menuStartWeighting->clear();
    _database.getAllVehicles(_vehicles);


    for (QVector<Vehicle*>::const_iterator vehicle(_vehicles.begin()); vehicle < _vehicles.end(); ++vehicle)
    {
        // It is for start a weighting.
        QAction* action = new QAction((**vehicle).name(), _menuStartWeighting);
        QVariant data(QVariant::fromValue(*vehicle));

        this->connect(action, SIGNAL(triggered()), this, SLOT(startWeighting()));
        this->connect(action, SIGNAL(triggered()), _ui->_scale, SLOT(start()));
        action->setData(data);
        _menuStartWeighting->addAction(action);
        _ui->_vehicleStack->addVehicle(action);

        // It is for manual input.
        action = new QAction((**vehicle).name(), _menuManualInput);
        action->setData(data);
        _menuManualInput->addAction(action);

        this->connect(action, SIGNAL(triggered()), this, SLOT(manualWeighting()));
    }
}

void MainWindow::addVehicle(void)
{
    CreateVehicleDialog dialog(this);

    if (dialog.exec() != QDialog::Accepted)
        return;

    // It is for the weighting stuff.
    QAction* action = new QAction(dialog.vehicle()->name(), _menuStartWeighting);
    QVariant data(QVariant::fromValue(dialog.vehicle()));

    _vehicles.push_back(dialog.vehicle());
    _database.addVehicle(dialog.vehicle());
    action->setData(data);
    this->connect(action, SIGNAL(triggered()), this, SLOT(startWeighting()));
    this->connect(action, SIGNAL(triggered()), _ui->_scale, SLOT(start()));
    _menuStartWeighting->addAction(action);
    _ui->_vehicleStack->addVehicle(action);


    // It is for the manual input.
    action = new QAction(dialog.vehicle()->name(), _menuManualInput);
    _menuManualInput->addAction(action);
    this->connect(action, SIGNAL(triggered()), this, SLOT(manualWeighting()));
}

void MainWindow::selectDatabase(void)
{
    DatabaseDialog dialog(_database, this);
    dialog.exec();
    this->getAllVehiclesFromDatabase();
    _ui->_goods->getAllGoodsFromDatabase();
    _ui->_suppliers->getAllSuppliersFromDatabase();
    _ui->_fields->getAllFieldsFromDatabase();
}

void MainWindow::startWeighting(void)
{
    qDebug() << __PRETTY_FUNCTION__;
    QAction* action = qobject_cast<QAction*>(this->sender());

    if (!action)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !action --> return";
        return;
    }

    Vehicle* vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }

    _menuStartWeighting->setDisabled(true);
    _menuManualInput->setDisabled(true);
    _ui->_vehicleStack->setDisabled(true);
    _cancelWeighting->setEnabled(true);
    _scale->start(vehicle, _ui->_goods->selectedId(), _ui->_suppliers->selectedId(), _ui->_fields->selectedId());
}

void MainWindow::stopWeighting(Weighting* weighting)
{
    _menuStartWeighting->setEnabled(true);
    _menuManualInput->setEnabled(true);
    _ui->_vehicleStack->setDisabled(false);
    _cancelWeighting->setDisabled(true);

    // Here is a memory leak!!!!
    if (weighting && weighting->valid())
        _database.addWeighting(weighting);
}

void MainWindow::manualWeighting(void)
{
    qDebug() << __PRETTY_FUNCTION__;

    _menuStartWeighting->setDisabled(true);
    _menuManualInput->setDisabled(true);
    _ui->_vehicleStack->setDisabled(true);

    // Check if the sender is an action.
    QAction* action = qobject_cast<QAction*>(this->sender());

    if (!action)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !action --> return";
        return;
    }

    // Check if the action contains a vehicle as action.
    Vehicle* vehicle = dynamic_cast<Vehicle*>(action->data().value<Vehicle*>());

    if (!vehicle)
    {
        qDebug() << __PRETTY_FUNCTION__ << ": !vehicle --> return";
        return;
    }


    // Execute the manual input dialog.
    ManualInputWidget dialog(vehicle,
                             _ui->_goods->selectedId(),
                             _ui->_suppliers->selectedId(),
                             _ui->_fields->selectedId(),
                             this);

    if (dialog.exec() == QDialog::Accepted)
    {
        _database.addWeighting(dialog.getWeighting());
    }

    _menuStartWeighting->setEnabled(true);
    _menuManualInput->setEnabled(true);
    _ui->_vehicleStack->setDisabled(false);
}
