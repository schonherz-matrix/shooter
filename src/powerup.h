#ifndef POWERUP_H
#define POWERUP_H

#include <QColor>
#include <QPropertyAnimation>
#include <array>
#include "collidingitem.h"

/**
 *  This class represents a PowerUp game item.
 *
 *  Constructing the item will spawn a random
 *  powerup to a random start-position on the
 *  edge of the scene.
 */
class PowerUp : public CollidingItem {
 public:
  enum { Type = UserType + 4 };

  int type() const override {
    // Enable the use of qgraphicsitem_cast with this item.
    return Type;
  }

  /**
   * @brief Constructor
   * @param scene A pointer to the scene where the powerup is to be placed
   */
  PowerUp(QGraphicsScene *scene);
  // CollidingItem interface
  void hit(Player *attacker) override;
  // QGraphicsItem interface
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
             QWidget *) override;
  QRectF boundingRect() const override;
  QPainterPath shape() const override;

  /**
   * @brief Enumeration of powerUp types
   */
  enum powerType {
    HEALTH,       /**< Heals the destroyer */
    DOUBLE_SHOOT, /**< Replaces the destroyers gun with a double shooting one
                     for some time */
    TRIPLE_SHOOT, /**< Replaces the destroyers gun with a triple shooting one
                     for some time */
    LASER,
    /**< Laser is cool. */  // TODO better specification
    NONE                    /**< Means no power */
  } power;

 private:
  /**
   * @brief The color of the powerup
   */
  QColor color;

  /**
   * @brief The displacement of the item in a very short time
   *
   *      dr  |
   * v =  --  |  =  this->speed
   *      dt  |
   *          | dt=time between renders
   */
  QPointF speed;

  /**
   * @brief There are this much possible combinations of power-color pairs
   */
  constexpr static size_t number_of_types = 4;
  /**
   * @brief power-color pairs
   */
  const static std::array<std::pair<powerType, QColor>, number_of_types> types;

  QPropertyAnimation anim;
};

#endif  // POWERUP_H
