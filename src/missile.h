#ifndef MISSILE_H
#define MISSILE_H

#include <QColor>
#include <QPointF>

#include "asteroid.h"
#include "collidingitem.h"
#include "player.h"
#include "powerup.h"
#include <QPropertyAnimation>

class Missile : public CollidingItem {
 public:
    enum { Type = UserType + 2 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

  Player* const owner;

  Missile(const QPointF& start_position, QColor color, Player* const owner,
          bool direction_down, int time = 3);
  QRectF boundingRect() const override;
  QPainterPath shape() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* item,
             QWidget* widget) override;
  void advance(int phase) override;

 private:
  QPointF direction;
  QColor color;
  QPropertyAnimation anim;

  // CollidingItem interface
 public:
  void hit(Player* p) override;
};

#endif  // MISSILE_H
