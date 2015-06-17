#include <QApplication>

#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    MainWindow* mw = MainWindow::instance();

    mw->show();

    return app.exec();
}
