#ifndef POWERUP_H
#define POWERUP_H

#include <QColor>
#include <QGraphicsItem>

class PowerUp : public QGraphicsItem
{
public:
    PowerUp();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    
    void advance(int phase) override;

private:
    struct {
        double x, y;
    } position;

    int x;
    int y;
    QColor color;

    enum type{
      HEALTH,
      DOUBLE_SHOOT,
      TRIPLE_SHOOT,
      LASER
    } power;

    struct {
        double move_in_x;
        double move_in_y;
    } speed;

    constexpr static size_t number_of_types = 4;
    const static std::array<std::pair<type, QColor>, number_of_types> types;
};


#endif // POWERUP_H
