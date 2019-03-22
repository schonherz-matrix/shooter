#ifndef POWERUP_H
#define POWERUP_H

#include <QColor>
#include <QGraphicsItem>
#include <array>
#include "collidingitem.h"

/**
 *  This class represents a PowerUp game item.
 *
 *  Constructing the item will spawn a random
 *  powerup to a random start-position on the
 *  edge of the scene.
 */
class PowerUp : public CollidingItem{
public:
    /**
     * @brief Constructor
     * @param scene A pointer to the scene where the powerup is to be placed
     */
    PowerUp(QGraphicsScene* scene);

    //QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    
    /**
     * @brief Steps the state of the game by one move.
     *        This function is called repeatedly.
     *        The time between the calles is definied in class MatrixScene
     * @param phase Between every render this function is called with phase=0 than phase=1
     * @see QGraphicsItem::advance(int)
     */
    void advance(int phase) override;

    /**
     * @brief Enumeration of powerUp types
     */
    enum powerType{
      HEALTH,        /**< Heals the destroyer */
      DOUBLE_SHOOT,  /**< Replaces the destroyers gun with a double shooting one for some time */
      TRIPLE_SHOOT,  /**< Replaces the destroyers gun with a triple shooting one for some time */
      LASER,         /**< Laser is cool. */ //TODO better specification
      NONE           /**< Means no power */
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

    // CollidingItem interface
public:
    void hit(Player *attacker) override;
};


#endif // POWERUP_H
