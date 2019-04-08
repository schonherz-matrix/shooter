#include "bar.h"

#include <QtDebug>
#include <QtWidgets>
#include "config.h"

Bar::Bar(const QColor &color, float default_value)
    : m_color{color}, anim(this, "value") {
  setValue(default_value);
  anim.setDuration(config::duration::powerup_effect.count());
  anim.setStartValue(1.0);
  anim.setEndValue(0);

  connect(&anim, &QPropertyAnimation::finished, this,
          [=]() { emit finished(); });
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

void Bar::setDuration(std::chrono::milliseconds value) {
  anim.setDuration(value.count());
}

void Bar::startAnim() { anim.start(); }

// drawing functions
//--------------------------------------------------------------------------------

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                QWidget *) {
  painter->setPen(m_color.darker());
  painter->drawLine(0, 0, 0, 25);  // Background
  painter->setPen(m_color);
  int startX = 25 - 25 * m_value;
  if (m_value > 0) painter->drawLine(0, startX, 0, 25);  // Foreground
}

QRectF Bar::boundingRect() const { return QRectF(0, 0, 1, 26); }

QPainterPath Bar::shape() const {
  QPainterPath path;
  path.addRect(0, 0, 0, 0);  // no collision
  return path;
}
