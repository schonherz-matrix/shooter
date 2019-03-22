#include "collidingitem.h"
#include <QDebug>
#include <QGraphicsScene>

bool CollidingItem::lookAround(Player* owner_of_observer){
    auto ci = collidingItems();

    if(ci.empty())
        return false;

    for(auto item: ci) {
        try{
            auto& nearby_object = dynamic_cast<CollidingItem&>(*item);
            nearby_object.hit(owner_of_observer);
        } catch(...){
            //The item wasn't a CollidingItem or hit thrown an error
        }
    }

    return true;
}

CollidingItem::CollidingItem(){
    qDebug() << "Constructed: " << this << "\n";
}

CollidingItem::~CollidingItem(){
    qDebug() << "Destructed: " << this << "\n";
}

void CollidingItem::remove(){
    scene()->removeItem(this);
    //delete this; TODO free memory

    //Story with simple delete____  deleting an object from the scene during the iteration of advance causes segfault.
    //TODO free memory somewhere else
    //This function is a placeholder for that function.
}
