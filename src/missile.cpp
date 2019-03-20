#include "missile.h"
#include <QPainter>

Missile::Missile(QPointF position) {
    if (direction_down) {
        position.setX(position.y() + 1);
    } else {
        position.setY(position.y() - 1);
    }
}

QRectF Missile::boundingRect() const {
    return QRectF(0,0,1,1);
}

QPainterPath Missile::shape() const {
    QPainterPath path;
    path.addRect(0,0,1,1);
    return path;
}
void Missile::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(color, 1));
    painter->drawPoint(0,0);

}

void Missile::setDirectionDown(bool direction_down){
    this->direction_down = direction_down;
}

