#include "hitindicator.h"

#include <QBrush>
#include <QPen>

HitIndicator::HitIndicator(qreal y, qreal width, qreal height, QColor color,
                           QGraphicsItem *parent)
    : QGraphicsRectItem(2, y, width, height, parent) {
  setPen(Qt::NoPen);
  setBrush(color);
}

QPainterPath HitIndicator::shape() const {
  QPainterPath path;
  path.addRect(0, 0, 0, 0);  // no collision
  return path;
}
