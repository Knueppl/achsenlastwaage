#include "axis_view.h"
#include "axis_items.h"
#include <QObject>
#include <iostream>

AxisView::AxisView(QWidget* parent) : QWidget(parent)
{
    m_graphicsScene = new QGraphicsScene(this);
    ItemWheel* newItem = new ItemWheel("./picture/rad_128x128.jpg");
    newItem->setVisible(false);
    m_graphicsScene->addItem(newItem);
    m_items.push_back(newItem);

    newItem = new ItemWheel("./picture/rad_128x128.jpg");
    newItem->setVisible(false);
    m_graphicsScene->addItem(newItem);
    m_items.push_back(newItem);

    newItem = new ItemWheel("./picture/rad_128x128.jpg");
    newItem->setVisible(false);
    m_graphicsScene->addItem(newItem);
    m_items.push_back(newItem);

    newItem = new ItemWheel("./picture/rad_128x128.jpg");
    newItem->setVisible(false);
    m_graphicsScene->addItem(newItem);
    m_items.push_back(newItem);

    newItem = new ItemWheel("./picture/rad_128x128.jpg");
    newItem->setVisible(false);
    m_graphicsScene->addItem(newItem);
    m_items.push_back(newItem);

    newItem = new ItemWheel("./picture/waage.jpg");
    newItem->setPos(0, 32);
    m_graphicsScene->addItem(newItem);

    m_graphicsView = new QGraphicsView(m_graphicsScene, this);
    m_graphicsView->setRenderHint(QPainter::Antialiasing);
    m_graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    m_graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_graphicsView);

    m_timer = new QTimer();
    QObject::connect(m_timer, SIGNAL(timeout()), m_graphicsScene, SLOT(advance()));
    m_timer->start(20);
}

AxisView::~AxisView(void)
{

}

void AxisView::startWeighting(void)
{
    QList<ItemWheel*>::iterator i;

    m_numberOfAxis = 5;
    m_currentAxis = 0;

    for (i = m_items.begin(); i != m_items.end(); ++i)
    {
        (*i)->setPos(150, 0);
        (*i)->setTarget(150, 0);
        (*i)->setVisible(false);
    }

    m_items.first()->setVisible(true);
    m_items.first()->setRotate(true);
}

void AxisView::nextState(void)
{
    if (++m_currentAxis > m_numberOfAxis)
    {
        this->stopWeighing();
        return;
    }

    for (int i = 0; i < m_currentAxis && i < m_items.size(); i++)
    {
        m_items.at(i)->setTarget(m_items.at(i)->pos().x() - 150, 0);
        m_items.at(i)->setVisible(true);
        m_items.at(i)->setRotate(true);
    }
}

void AxisView::stopWeighing(void)
{
    QList<ItemWheel*>::iterator i;

    for (i = m_items.begin(); i != m_items.end(); ++i)
    {
        (*i)->setRotate(false);
    }
}
