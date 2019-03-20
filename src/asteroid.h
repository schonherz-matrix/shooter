#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>

class Asteroid : public QGraphicsItem {
private:

    static constexpr int MAXLIFE = 2;

    int type;
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
    Asteroid();

    void hit();

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void advance(int phase) override;
};

#endif // ASTEROID_H
