#ifndef MISSILE_H
#define MISSILE_H

#include <QColor>
#include <QPointF>

#include "asteroid.h"
#include "collidingitem.h"
#include "player.h"
#include "powerup.h"

class Missile : public CollidingItem {
 public:
  enum { Type = UserType + 2 };

  int type() const override {
    return Type;
  }

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

  // CollidingItem interface
 public:
  void hit(QGraphicsItem* item) override;
};

#endif  // MISSILE_H
