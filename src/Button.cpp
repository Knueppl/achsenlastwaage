#include "Button.h"

#include <QPainter>
#include <QPalette>

Button::Button(QGraphicsItem* parent)
    : QGraphicsObject(parent),
      _size(100, 40)
{

}

QRectF Button::boundingRect(void) const
{
    return QRectF(-_size.width() / 2, -_size.height() / 2, _size.width(), _size.height());
}

void Button::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QPalette().brush(QPalette::Background));
    painter->drawRoundedRect(this->boundingRect(), 2, 2);
}
