#ifndef Player_H
#define Player_H

#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>
#include <QColor>
#include <QObject>

constexpr size_t max_life = 100;

class Player : public QGraphicsItem, public QObject
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
    Q_PROPERTY(size_t life MEMBER life READ getLife)

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
