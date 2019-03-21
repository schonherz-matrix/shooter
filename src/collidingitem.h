#ifndef COLLIDINGITEMS_H
#define COLLIDINGITEMS_H

#include <QGraphicsItem>

class CollidingItem : public QGraphicsItem
{
public:
    CollidingItem();
    virtual ~CollidingItem(){}

    virtual void hit(QGraphicsItem* item) = 0;

    // QGraphicsItem interface
public:
    void advance(int phase) override;
};

#endif // COLLIDINGITEMS_H
