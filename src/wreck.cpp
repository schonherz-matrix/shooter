#include "wreck.h"

#include <QGraphicsScene>
#include <QDebug>
#include "missile.h"

Wreck::Wreck(QPointF pos, QColor color)
    : color(color), position(pos)
{
    QRandomGenerator& generator = *QRandomGenerator::system();


    this->speed.setX(static_cast<float>(generator.bounded(10,20)) / (generator.bounded(1000)));
    if(generator.generate() % 2 ? true : false){
        this->speed.setX(-1 * this->speed.x());
    }
    this->speed.setY(static_cast<float>(generator.bounded(10,20)) / (generator.bounded(1000)));
    if(generator.generate() % 2 ? true : false){
        this->speed.setY(-1 * this->speed.y());
    }

    setPos(position.x(), position.y());
}

void Wreck::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(this->color, 1));
    painter->drawPoint(0, 0);
}

QRectF Wreck::boundingRect() const {
    return QRectF(0, 0, 1, 1);
}

QPainterPath Wreck::shape() const {
    QPainterPath path;
    path.addRect(0, 0, 0, 0);

    return path;
}

void Wreck::advance(int phase) {
    if (phase == 0)
        return;

    this->moveBy(speed.x(), speed.y());

    if ( this->pos().x() > 32 || this->pos().x() < 0 ||
            this->pos().y() < 0 || this->pos().y() > 26 ) {
        remove();
    }
}

void Wreck::hit(Player *)
{
    //remove();
}
