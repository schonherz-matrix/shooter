#ifndef WRECK_H
#define WRECK_H

#include <QPainter>
#include <QRandomGenerator>
#include "collidingitem.h"
#include <QMediaPlayer>

class Wreck : public QGraphicsItem {
private:
    int look;

    QColor color;

    QPointF speed;

    QPointF position;

public:
    Wreck(QPointF pos, QColor color);

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void advance(int phase) override;

};

#endif // WRECK_H
