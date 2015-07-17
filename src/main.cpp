#include <QApplication>

#include "MainWindow.h"

int main(int argc, char** argv)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    MainWindow* mw = MainWindow::instance();

    mw->show();

    return app.exec();
}
