#include "laser.hpp"

#include <QPainter>
#include "player.h"

Laser::Laser(Player *const owner, bool direction_down)
    : owner(owner), shooting_down(direction_down) {
  updatePos();
}

QRectF Laser::boundingRect() const { return QRectF(0, 0, 1, Laser::height); }

void Laser::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                  QWidget *) {
  painter->setPen(QPen(owner->getColor(), 1));
  painter->drawLine(0, 0, 0, height);
}

void Laser::updatePos() {
  if (shooting_down)
    setPos(owner->pos() + QPointF(1, 2));
  else
    setPos(owner->pos().x() + 1, owner->pos().y() - height - 1);
}

void Laser::advance(int phase) {
  if (phase == 0) {
    if (owner->getPowerUp() != PowerUp::LASER) remove();

    lookAround(owner);
    updatePos();
  }
}

void Laser::hit(Player *) { return; }
