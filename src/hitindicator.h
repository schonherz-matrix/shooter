#ifndef HITINDICATOR_H
#define HITINDICATOR_H

#include <QGraphicsRectItem>

class HitIndicator : public QGraphicsRectItem {
 public:
  HitIndicator(qreal y, qreal width, qreal height, QColor color,
               QGraphicsItem *parent = nullptr);

  // QGraphicsItem interface
 public:
  QPainterPath shape() const override;
};

#endif  // HITINDICATOR_H
