#ifndef MISSILE_H
#define MISSILE_H

#include <QColor>
#include <QGraphicsItem>
#include <QPointF>
#include "asteroid.h"
#include "player.h"
#include "powerup.h"

class Missile : public QGraphicsItem {
 public:
  const QGraphicsItem* parent;

  Missile(const QPointF& start_position, QColor color, QGraphicsItem* owner,
          bool direction_down);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
             QWidget* widget) override;
  void advance(int phase) override;

 private:
  QPointF speed;
  QColor color;

 public:
  void meetWith(PowerUp&);
  void meetWith(Asteroid&);
  void meetWith(Player&);
};

#endif  // MISSILE_H
