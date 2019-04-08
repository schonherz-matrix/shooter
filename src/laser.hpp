#pragma once
#include "collidingitem.h"

class Laser final: public CollidingItem{
    Player* const owner;
    bool shooting_down;

    constexpr static size_t height = 30;

    void updatePos();
public:
    explicit Laser(Player* const owner, bool direction_down);
    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*,
               QWidget*) override;
    void advance(int phase) override;
    //QPainterPath shape() const override;

    // CollidingItem interface
public:
    void hit(Player*) override;
};
