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
#include <SFML/Audio.hpp>

class MatrixScene;

constexpr size_t max_life = 100;

class Player :  public CollidingItem
{
    Q_OBJECT
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
    bool dead;
    sf::Sound sound;

public:
    enum { Type = UserType + 1 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }
    Player(bool upper, QGamepad *gamepad, Bar *healthBar, Bar *powerUp, MatrixScene* MScene);

    QColor getColor() {return this->color;}
    PowerUp::powerType getPowerUp() {return this->power;}

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
    void hurt(size_t loss); //when a player gets hurt; its HP lessens by loss

    void applyPowerUp(PowerUp::powerType const pu);
    void loosePower();
    size_t getLife() {
        return this->life;
    }
    void fire();
    void moveLeft();
    void moveRight();

signals:
    void gameOver(bool upper);

private:
    unsigned time_to_fire;
    void displayHealth();
    void displayPowerUp();

    // CollidingItem interface
public:
    void hit(Player *item) override;

    PowerUp::powerType power;
    unsigned time_from_power;

};

#endif // Player_H
