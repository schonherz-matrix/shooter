#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>

class Asteroid : public QGraphicsItem
{
    int m_x, m_y;
    int type;

    static const int MAXLIFE = 3;

    QColor color;

    int life;

public:
    Asteroid();

    int getX() {
        return this->m_x;
    }

    int getY() {
        return this->m_y;
    }

    void setX(int x) {
        m_x = x;
    }

    void setY(int y) {
        m_y = y;
    }

    // QGraphicsItem interface
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
};

#endif // ASTEROID_H
