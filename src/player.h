#ifndef Player_H
#define Player_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QColor>

#include "bar.h"

constexpr size_t max_life = 100;

class Player : public QGraphicsItem
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
    Bar *bar;

    const bool upper;
    QColor color;
    size_t life;

public:
    Player(bool upper, Bar *bar);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;

    size_t getLife() {
        return this->life;
    }
};

#endif // Player_H
