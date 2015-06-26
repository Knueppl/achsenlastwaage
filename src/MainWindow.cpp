#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CreateVehicleDialog.h"
#include "DatabaseDialog.h"

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
      _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);

    /* Initialize the database. */
    _database.connect("biogasernte2015");
//    _database.create();

    /* Create menus. */
    QMenuBar* bar = this->menuBar();
    QMenu* menu = bar->addMenu("Fahrzeuge");
    _menuStartWeighting = menu->addMenu("Starte Wiegung");
    menu->addAction("Hinzufügen", this, SLOT(addVehicle()));

    menu = bar->addMenu("Datenbank");
    menu->addAction("Auswählen", this, SLOT(selectDatabase()));
}

MainWindow::~MainWindow(void)
{

}

void MainWindow::addVehicle(void)
{
    CreateVehicleDialog dialog;

    if (dialog.exec() != QDialog::Accepted)
        return;

    QAction* action = new QAction(dialog.vehicle()->name(), this);
    QVariant data(QVariant::fromValue(dialog.vehicle()));

    _vehicles.push_back(dialog.vehicle());
    action->setData(data);
    _menuStartWeighting->addAction(action);
}

void MainWindow::selectDatabase(void)
{
    DatabaseDialog dialog(_database, this);
    dialog.exec();
}
