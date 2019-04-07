#include "laser.hpp"
#include "player.h"
#include <QPainter>

Laser::Laser(Player* const owner, bool direction_down):
    owner(owner),
    energy_used(0),
    shooting_down(direction_down)
{
    updatePos();
}

QRectF Laser::boundingRect() const {
    return QRectF(0, 0, 1, Laser::height);
}

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(QPen(owner->getColor(), 0));
    painter->setBrush(owner->getColor());
    painter->drawRect(this->boundingRect());
}

void Laser::updatePos(){
    if (shooting_down)
        setPos(0.5+owner->x(),owner->y()+2.5);
    else
        setPos(0.5+owner->x(),owner->y()-1-Laser::height);
}

void Laser::advance(int phase) {
    if(phase == 0){
        if(owner->getPowerUp()!=PowerUp::LASER)
            remove();

        updatePos();

        if (lookAround(owner)){
            energy_used++;
            if(energy_used == 3){ //TODO move to config
                owner->loosePower();
                remove();
            }
            return;
        }
    }
}

void Laser::hit(Player *)
{
    return;
}
