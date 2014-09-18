#ifndef ___BUTTON_H___
#define ___BUTTON_H___

#include <QGraphicsObject>

class Button : public QGraphicsObject
{
    Q_OBJECT

public:
    Button(QGraphicsItem* parent = 0);

    virtual QRectF boundingRect(void) const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
    QSize _size;
};

#endif
