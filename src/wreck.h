#ifndef WRECK_H
#define WRECK_H

#include <QPainter>
#include <QRandomGenerator>
#include "collidingitem.h"

class Wreck : public QGraphicsItem {
private:
    int look;

    QColor color;

    QPointF speed;

    QPointF position;

public:
    enum { Type = UserType + 6 };

    int type() const override
    {
        // Enable the use of qgraphicsitem_cast with this item.
        return Type;
    }

    Wreck(QPointF pos, QColor color);

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void advance(int phase) override;

};

#endif // WRECK_H
