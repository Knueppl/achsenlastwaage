#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow* MainWindow::_instance = 0;

MainWindow* MainWindow::instance(void)
{
    if (!_instance)
        _instance = new MainWindow;

    return _instance;
}

MainWindow::MainWindow(void)
    : _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
}
