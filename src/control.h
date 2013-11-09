#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTabWidget>
#include "vehicle_manager.h"
#include "axis_view.h"
#include "weight_list.h"
#include "fzw12.h"
#include "camera.h"

class Control : public QWidget
{
    Q_OBJECT;

public:
    Control(QWidget* parent = 0);
    ~Control(void);

    void startWeighting(Weight* weight);
    void abortWeighting(void);

public slots:
    void nextAxis(int, Weight*);
    void finishWeight(Weight* weight);
    void tabLeft(void);
    void tabRight(void);

private:
    VehicleManager* m_manager;
    AxisView*       m_axisView;
    WeightList*     m_weightList;
    WeightHandler   m_weightHandler;
    Camera*         m_camera;
#ifdef _DEBUG_
    Dummy*          m_waage;
#else
    FZW12*          m_fzw12;
#endif

    QVBoxLayout*    m_mainLayout;
    QHBoxLayout*    m_firstRow;
    QHBoxLayout*    m_secondRow;
    QTabWidget*     m_tabs;
};

#endif
