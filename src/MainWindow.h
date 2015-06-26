#ifndef ___MAIN_WINDOW_H___
#define ___MAIN_WINDOW_H___

#include <QMainWindow>

#include "Database.h"

class Vehicle;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow* instance(void);

private:
    MainWindow(void);
    virtual ~MainWindow(void);

    Ui::MainWindow* _ui;
    Database _database;
    QVector<Vehicle*> _vehicles;
    QVector<QAction*> _startWeighting;
    QMenu* _menuStartWeighting;

    static MainWindow* s_instance;

private slots:
    void addVehicle(void);
    void selectDatabase(void);
};

#endif
