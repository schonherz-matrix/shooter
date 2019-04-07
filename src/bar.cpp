#include "bar.h"

#include <QtDebug>
#include <QtWidgets>

Bar::Bar(const QColor &color, float default_value) : m_color{color} {
  setValue(default_value);
}

// getters, setters
//--------------------------------------------------------------------------------
void Bar::setValue(float val) {
  if (val < 0)
    m_value = 0.0;
  else if (val > 1.0)
    m_value = 1.0;
  else
    m_value = val;
  update();
}

float Bar::getValue() { return m_value; }

void Bar::setColor(const QColor &color) { m_color = color; }

QColor &Bar::getColor() { return m_color; }

// drawing functions
//--------------------------------------------------------------------------------

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
                QWidget *widget) {
  Q_UNUSED(item)
  Q_UNUSED(widget)

  painter->setPen(m_color.darker());
  painter->drawLine(0, 0, 0, 25);  // Background
  painter->setPen(m_color);
  int startX = 25 - 25 * m_value;
  if (m_value > 0) painter->drawLine(0, startX, 0, 25);  // Foreground
}

QRectF Bar::boundingRect() const { return QRectF(0, 0, 1, 26); }

QPainterPath Bar::shape() const {
  QPainterPath path;
  path.addRect(boundingRect());
  return path;
}
