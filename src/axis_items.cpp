#include "axis_items.h"

#include <QPainter>
#include <iostream>
#include <QDebug>

ItemWheel::ItemWheel(void)
{
    m_picture = new QPixmap();
    m_rotate = false;
}

ItemWheel::ItemWheel(const QString& pictureName)
{
    m_picture = new QPixmap(pictureName);
    m_outline = QRectF(m_picture->rect().x() - m_picture->rect().width() / 2, m_picture->rect().y() - m_picture->rect().height() / 2,
                       m_picture->rect().width(), m_picture->rect().height());
    m_rotate = false;
}

ItemWheel::~ItemWheel(void)
{

}

QRectF ItemWheel::boundingRect(void) const
{
    return m_outline;
}

void ItemWheel::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawPixmap(m_outline.x(), m_outline.y(), *m_picture);
}

void ItemWheel::advance(int)
{
    if (!m_rotate)
    {
        return;
    }

    this->setRotation(this->rotation() - 1.0);

    if (m_target != this->pos())
    {
        qreal newX = this->pos().x(), newY = this->pos().y();

        if (m_target.x() > this->pos().x())
        {
            newX = this->pos().x() + 2;
        }
        else if (m_target.x() < this->pos().x())
        {
            newX = this->pos().x() - 2;
        }

        if (m_target.y() > this->pos().y())
        {
            newY = this->pos().y() + 2;
        }
        else if (m_target.y() < this->pos().y())
        {
            newY = this->pos().y() - 2;
        }

        this->setPos(newX, newY);
    }
}

void ItemWheel::setTarget(const QPointF& target)
{
    m_target = target;
}

void ItemWheel::setTarget(const qreal x, const qreal y)
{
    m_target = QPointF(x, y);
}

void ItemWheel::setRotate(const bool state)
{
    m_rotate = state;
}
