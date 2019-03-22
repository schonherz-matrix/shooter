#ifndef Player_H
#define Player_H

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include <QtGamepad>

#include "bar.h"
#include "asteroid.h"
#include "powerup.h"
#include "collidingitem.h"

constexpr size_t max_life = 100;

class Player :  public CollidingItem
{
    /*
     * UPPER:
     *  XXX
     *   X
     *
     * LOWER:
     *   X
     *  XXX
     */
    QGamepad *gamepad;
    Bar *healthBar;
    Bar *powerUp;

    const bool upper;
    QColor color;
    size_t life;

public:
    Player(bool upper, QGamepad *gamepad, Bar *healthBar, Bar *powerUp);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void hurt(size_t loss); //when a player gets hurt; its HP lessens by loss
    void applyPowerUp(PowerUp::powerType const& pu);

    size_t getLife() {
        return this->life;
    }

private:
    unsigned time_to_fire;

    // CollidingItem interface
public:
    void hit(Player *item) override;
};

#endif // Player_H
