#include "collidingitem.h"

CollidingItem::CollidingItem()
{

}

void CollidingItem::advance(int phase)
{
    if(!phase) return;

    // collision
    foreach(auto item, collidingItems()) {
        static_cast<CollidingItem* >(item)->hit(this);
    }
}
