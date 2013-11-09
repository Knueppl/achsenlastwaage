#ifndef _AXIS_VIEW_H_
#define _AXIS_VIEW_H_

#include <QWidget>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QTimer>
#include "axis_items.h"

class AxisView : public QWidget
{
    Q_OBJECT

public:
    AxisView(QWidget* parent = 0);
    ~AxisView(void);

public slots:
    void startWeighting(void);
    void nextState(void);
    void stopWeighing(void);

private:
    QGraphicsView*    m_graphicsView;
    QGraphicsScene*   m_graphicsScene;
    QHBoxLayout*      m_mainLayout;
    QTimer*           m_timer;
    QList<ItemWheel*> m_items;

    int               m_numberOfAxis;
    int               m_currentAxis;
};

#endif
