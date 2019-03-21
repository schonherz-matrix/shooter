#ifndef POWERUP_H
#define POWERUP_H

#include <QColor>
#include <QGraphicsItem>
#include <array>

class PowerUp : public QGraphicsItem
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

    enum type{
      HEALTH,
      DOUBLE_SHOOT,
      TRIPLE_SHOOT,
      LASER
    } power;

    void kill();

private:
    QColor color;

    QPointF speed;

    constexpr static size_t number_of_types = 4;
    const static std::array<std::pair<type, QColor>, number_of_types> types;

public:
    const type getPower() const;
};


#endif // POWERUP_H
