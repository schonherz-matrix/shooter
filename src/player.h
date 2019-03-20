#ifndef Player_H
#define Player_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QColor>

constexpr size_t max_life = 100;

class Player : public QGraphicsItem
{
    Q_OBJECT

    /*
     * UPPER:
     *  XXX
     *   X
     *
     * LOWER:
     *   X
     *  XXX
     */
    const bool upper;
    QColor color;

    size_t life;

public:
    Player(bool upper);

    // QGraphicsItem interface
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    size_t getLife() {
        return this->life;
    }
};

#endif // Player_H
