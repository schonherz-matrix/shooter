#ifndef ASTEROID_H
#define ASTEROID_H

#include <QPainter>
#include <QRandomGenerator>
#include "collidingitem.h"
#include <QPropertyAnimation>
#include <SFML/Audio.hpp>

class MatrixScene;

class Asteroid : public CollidingItem {
private:

    static constexpr int MAXLIFE = 2;

    int life;

    QGraphicsPixmapItem pixmapItem;
    QPropertyAnimation anim;

public:
    enum { Type = UserType + 3 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    enum class AsteroidType {
        SMALL = 0,
        MEDIUM = 1,
        LARGE = 2
    };

    Asteroid(MatrixScene* MScene, QVector<QPointF> players);

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    // CollidingItem interface
    void hit(Player* attacker) override;
    bool removeAble();
    bool deleteAble();

private:
    AsteroidType look;
    sf::Sound sound;
};

#endif // ASTEROID_H
