#ifndef POWERUP_H
#define POWERUP_H

#include <QColor>
#include <QGraphicsItem>
#include <array>

class PowerUp : public QGraphicsItem
{
public:
    PowerUp();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    
    void advance(int phase) override;

private:
    QColor color;

    QPointF speed;

    enum type{
      HEALTH,
      DOUBLE_SHOOT,
      TRIPLE_SHOOT,
      LASER
    } power;

    constexpr static size_t number_of_types = 4;
    const static std::array<std::pair<type, QColor>, number_of_types> types;

public:
    const type getPower() const;
};


#endif // POWERUP_H
