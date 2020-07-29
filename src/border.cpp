#include "border.h"

#include <QPainter>
#include "config.h"

Border::Border(bool upper) {
  if (upper)
    setPos(0, 0);
  else
    setPos(0, config::borderYPos);

  setZValue(-1);
}

QRectF Border::boundingRect() const { return QRectF(0, 0, 28, 1); }

QPainterPath Border::shape() const {
  QPainterPath path;
  path.addRect(0, 0, 0, 0);  // no collision
  return path;
}

void Border::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                   QWidget *) {
  painter->setPen(QPen(Qt::gray, 1));
  painter->drawLine(0, 0, 29, 0);
}
