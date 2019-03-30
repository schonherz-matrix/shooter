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

    int look;
    int life;

    QColor color;

    int pieces[4][4];

    QMediaPlayer p;
    QPropertyAnimation anim;

public:
    Asteroid(QGraphicsScene* scene);

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    // CollidingItem interface
public:
    void hit(Player* attacker) override;
};

#endif // ASTEROID_H
