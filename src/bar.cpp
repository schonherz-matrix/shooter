#include "bar.h"
#include <QtWidgets>

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{
    Q_UNUSED(widget)

    QPen oldPen = painter->pen();
    QPen pen = oldPen;

    pen.setWidth(1);
    pen.setColor(m_color);

    int startX = 0;
    int startY = 25-(int)((m_value + 1.0/52.0) * 26.0);
    int endX = 0;
    int endY = 25;
    painter->drawLine(startX, startY, endX, endY);

    painter->setPen(oldPen);
}

void Bar::setValue(float val)
{
    if (val < 0) m_value = 0.0;
    else if(val > 1.0) m_value = 1.0;
    else m_value = val;
}



Bar::Bar(const QColor &color, float default_value) : m_color{color} {
    setValue(default_value);
}
