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
    qDebug() << "Constructed: " << this << "\n"; //TODO remove
}

CollidingItem::~CollidingItem(){
    qDebug() << "Destructed: " << this << "\n"; //TODO remove
}

void CollidingItem::remove(){
    scene()->removeItem(this);
    //delete this; TODO free memory

    //Story with simple delete____  deleting an object from the scene during the iteration of advance causes segfault.
    //TODO free memory somewhere else
    //This function is a placeholder for that function.

    //https://forum.qt.io/topic/50300/solved-remove-an-item-from-the-child-items-list-of-qgraphicsitem/9
    //https://github.com/qt/qtbase/blob/5.12/src/widgets/graphicsview/qgraphicsscene.cpp#L3302

    //maybe an other 'advance' function is the soultion
}
