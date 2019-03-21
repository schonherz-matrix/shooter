#ifndef ASTEROID_H
#define ASTEROID_H

#include <QPainter>
#include <QRandomGenerator>
#include "collidingitem.h"

class Asteroid : public CollidingItem {
private:

    static constexpr int MAXLIFE = 2;

    int look;
    int life;

    QColor color;

    int pieces[4][4];

    struct {
        float move_in_x;
        float move_in_y;
    } speed;

    struct {
        double x, y;
    } position;


public:
    enum { Type = UserType + 4 };

    int type() const override
    {
        return Type;
    }

    Asteroid();

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void advance(int phase) override;

    // CollidingItem interface
public:
    void hit(QGraphicsItem *item) override;
};

#endif // ASTEROID_H
