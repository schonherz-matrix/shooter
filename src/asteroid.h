#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>

class Asteroid : public QGraphicsItem
{
    int type;

    static const int MAXLIFE = 3;

    QColor color;

    int life;

public:
    Asteroid();

    void hit() {
        if (this->life > 0) this->life--;
    }

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};

#endif // ASTEROID_H
