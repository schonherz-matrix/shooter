#ifndef ASTEROID_H
#define ASTEROID_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRandomGenerator>

class Asteroid : public QGraphicsItem
{
    Q_OBJECT
    int m_x, m_y;
    int type;

    Q_PROPERTY(int x MEMBER m_x READ getX WRITE setX)
    Q_PROPERTY(int y MEMBER m_y READ getY WRITE setY)

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
