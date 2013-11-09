#include <Qt/QtGui>
#include <QTextCodec>
#include "control.h"

const int size_x = 640;
const int size_y = 640;

int main(int argc, char** argv)
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication app(argc, argv);
    app.setStyleSheet("QGroupBox {"
                      "border: 2px solid gray;"
                      "border-radius: 3px;"
                      "margin-top: 1ex }"
                      "QGroupBox::title {"
                      "subcontrol-origin: margin;"
                      "subcontrol-position: top center;"
                      "padding: 0 3px; }");

    Control control;
    control.resize(size_x, size_y);
    control.show();

    return app.exec();
}
