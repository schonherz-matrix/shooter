#ifndef MISSILE_H
#define MISSILE_H

#include <QColor>
#include <QGraphicsItem>


class Missile : public QGraphicsItem {
public:
    Missile(QPointF position, bool direction_down);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

private:
    bool direction_down;
    QColor color = Qt::magenta;
};

#endif // MISSILE_H
