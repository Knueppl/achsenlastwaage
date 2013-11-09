#ifndef _AXIS_ITEMS_H_
#define _AXIS_ITEMS_H_

#include <QGraphicsItem>
#include <QObject>
#include <QPicture>

class ItemWheel : public QObject, public QGraphicsItem
{
public:
    ItemWheel(void);
    ItemWheel(const QString& pictureName);
    ~ItemWheel(void);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setTarget(const QPointF& target);
    void setTarget(const qreal x, const qreal y);
    void setRotate(const bool state);

protected:
    void advance(int);

private:
    QPixmap* m_picture;
    QRectF   m_outline;
    QPointF  m_target;
    bool     m_rotate;
};

#endif
