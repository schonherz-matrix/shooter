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

constexpr size_t max_life = 2228;

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
    size_t getLife() {
        return this->life;
    }

    void moveLeft();
    void moveRight();
    void fire(bool fire = false);

private:
    std::chrono::milliseconds time_to_fire;
    int fireTimerID = 0;
    bool timerStarted = false;
    void displayHealth();
    void startFireTimer(std::chrono::milliseconds);
    bool canFire = false;
    QGraphicsRectItem* hitIndicator = nullptr;

    // CollidingItem interface
public:
    void hit(Player *item) override;

    PowerUp::powerType power;


    // QObject interface
protected:
    void timerEvent(QTimerEvent *event) override;
};

#endif // Player_H
