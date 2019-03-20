#include "bar.h"

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget)
{

}

void Bar::setValue(float val)
{
    if (val >= 0 || val <= 1.0) m_value=val;
}



Bar::Bar(const QColor &color, float default_value) : m_color{color} {
    setValue(default_value);
}
