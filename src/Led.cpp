#include "Led.h"

#include <QPainter>

LED::LED(const QColor& color, QWidget* parent)
    : QWidget(parent)
{
    m_state = false;
    m_color = color;
}

void LED::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QLinearGradient linearGrad(QPointF(0, 0), QPointF(this->width(), this->height()));
    if (!this->isEnabled())
    {
        linearGrad.setColorAt(0, Qt::gray);
        linearGrad.setColorAt(1, QColor(Qt::gray).darker());
    }
    else if (m_state)
    {
        linearGrad.setColorAt(0, m_color);
        linearGrad.setColorAt(1, m_color.darker());
    }
    else
    {
        linearGrad.setColorAt(0, m_color.darker(300));
        linearGrad.setColorAt(1, m_color.darker(500));
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(linearGrad));
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawEllipse(1, 1, this->width() - 2, this->height() - 2);
}

