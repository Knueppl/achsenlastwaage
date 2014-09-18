#include <QApplication>

#include "Database.h"
#include "Vehicle.h"
#include "MainWindow.h"

const int size_x = 640;
const int size_y = 640;

int main(int argc, char** argv)
{
//    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
//    Database database;
//    database.connect("achsenlastwaage");
//    std::vector<Vehicle*> vehicles;
//    database.getAllVehicles(vehicles);

    MainWindow* mw = MainWindow::instance();

    mw->show();

    return app.exec();
}
