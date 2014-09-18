#ifndef ___MAIN_WINDOW_H___
#define ___MAIN_WINDOW_H___

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
public:

    static MainWindow* instance(void);

private:
    MainWindow(void);

    Ui::MainWindow* _ui;

    static MainWindow* _instance;
};

#endif
