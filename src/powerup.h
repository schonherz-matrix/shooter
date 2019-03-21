#ifndef POWERUP_H
#define POWERUP_H

#include <QColor>
#include <QGraphicsItem>
#include <array>
#include "collidingitem.h"

class PowerUp : public CollidingItem
{
public:
    enum { Type = UserType + 5 };

    int type() const override
    {
        return Type;
    }

    PowerUp();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    
    void advance(int phase) override;

    enum powerType{
      HEALTH,
      DOUBLE_SHOOT,
      TRIPLE_SHOOT,
      LASER
    } power;

private:
    QColor color;

    QPointF speed;

    constexpr static size_t number_of_types = 4;
    const static std::array<std::pair<powerType, QColor>, number_of_types> types;

public:
    const powerType getPower() const;

    // CollidingItem interface
public:
    void hit(QGraphicsItem *item) override;
};


#endif // POWERUP_H
