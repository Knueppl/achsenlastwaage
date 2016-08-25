#ifndef ___MAIN_WINDOW_H___
#define ___MAIN_WINDOW_H___

#include <QMainWindow>

#include "Database.h"
#include "DummyScale.h"
#include "DummyScaleWidget.h"

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

    void getAllVehiclesFromDatabase(void);

    Ui::MainWindow* _ui;
    Database _database;
    Scale* _scale;
    DummyScaleWidget* _scaleWidget;

    QVector<Vehicle*> _vehicles;
    QVector<QAction*> _startWeighting;
    QMenu* _menuStartWeighting;
    QMenu* _menuManualInput;
    QAction* _cancelWeighting;

    static MainWindow* s_instance;

private slots:
    void addVehicle(void);
    void selectDatabase(void);
    void startWeighting(void);
    void stopWeighting(Weighting*);
    void manualWeighting(void);
};

#endif
