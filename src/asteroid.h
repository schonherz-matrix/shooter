#ifndef ASTEROID_H
#define ASTEROID_H

#include <QPainter>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <SFML/Audio.hpp>
#include "collidingitem.h"

class MatrixScene;

class Asteroid : public CollidingItem {
 public:
  enum { Type = UserType + 3 };

  int type() const override {
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
  }

  enum class AsteroidType { SMALL = 0, MEDIUM = 1, LARGE = 2 };

  Asteroid(MatrixScene *MScene);

  // QGraphicsItem interface
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
             QWidget *widget) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  // CollidingItem interface
  void hit(Player *attacker) override;
  bool removeAble();
  bool deleteAble();

 private:
  AsteroidType look;
  sf::Sound sound;
  static constexpr int MAXLIFE = 2;
  int life;
  QGraphicsPixmapItem pixmapItem;
  QPropertyAnimation anim;
};

#endif  // ASTEROID_H
