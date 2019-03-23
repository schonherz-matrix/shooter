#include "bar.h"

#include <QtWidgets>
#include <QtDebug>

Bar::Bar(const QColor &color, float default_value) : m_color{color} {
    setValue(default_value);
}

//getters, setters
//--------------------------------------------------------------------------------
void Bar::setValue(float val)
{
    if (val < 0) m_value = 0.0;
    else if(val > 1.0) m_value = 1.0;
    else m_value = val;
}

float Bar::getValue()
{
    return m_value;
}

void Bar::setColor(const QColor &color)
{
    m_color = color;
}

QColor &Bar::getColor()
{
    return m_color;
}

//drawing functions
//--------------------------------------------------------------------------------

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget)

    QPen pen(m_color, 1);
    painter->setPen(pen);

    int pixVal = (int)((m_value + 1.0/52.0) * 26.0);

    int startX = 0;
    int startY = 26-pixVal;
    int endX = 0;
    int endY = 25;
    if (pixVal == 1)
    {
        painter->drawPoint(endX, endY);
    }
    else if (pixVal > 0)
    {
        painter->drawLine(startX, startY, endX, endY);
    }
}

QRectF Bar::boundingRect() const
{
    return QRectF(0, 0, 1, 26);
}

QPainterPath Bar::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
