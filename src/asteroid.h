#ifndef ASTEROID_H
#define ASTEROID_H

#include <QPainter>
#include <QRandomGenerator>
#include "collidingitem.h"
#include <QMediaPlayer>
#include <QPropertyAnimation>

class Asteroid : public CollidingItem {
private:

    static constexpr int MAXLIFE = 2;

    int life;

    QGraphicsPixmapItem pixmapItem;

    QMediaPlayer p;
    QPropertyAnimation anim;

public:
    enum class AsteroidType {
        SMALL = 0,
        MEDIUM = 1,
        LARGE = 2
    };

    Asteroid(QGraphicsScene* scene);

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    // CollidingItem interface
public:
    void hit(Player* attacker) override;

private:
    AsteroidType type;
};

#endif // ASTEROID_H
