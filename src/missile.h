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
  Player* const owner;

  Missile(const QPointF& start_position, QColor color, Player* const owner,
          bool direction_down);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
             QWidget* widget) override;
  void advance(int phase) override;

 private:
  QPointF speed;
  QColor color;

  // CollidingItem interface
 public:
  void hit(Player* p) override;
};

#endif  // MISSILE_H
