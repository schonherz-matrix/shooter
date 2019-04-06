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
    return QRectF(0, 0, 0, Laser::height);
}

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    painter->setPen(QPen(owner->getColor(), 1));
    painter->drawRect(this->boundingRect());
}

void Laser::updatePos(){
    if (shooting_down)
        setPos(1+owner->x(),owner->y()+2);
    else
        setPos(1+owner->x(),owner->y()-2-Laser::height);
}

void Laser::advance(int phase) {
    if(phase == 0){
        if(owner->getPowerUp()!=PowerUp::LASER)
            remove();

        updatePos();

        if (lookAround(owner)){
            energy_used++;
            if(energy_used == 3){ //TODO move to config
                owner->applyPowerUp(PowerUp::NONE);
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
