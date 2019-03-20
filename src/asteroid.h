#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>

class Asteroid : public QGraphicsItem
{
    static const int MAXLIFE = 3;

    int type;
    int life;

    QColor color;

    int pieces[4][4];

public:
    Asteroid();

    void hit();

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};

#endif // ASTEROID_H
