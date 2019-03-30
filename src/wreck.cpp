#include "wreck.h"

#include <QGraphicsScene>
#include <QDebug>
#include "missile.h"

Wreck::Wreck(QPointF pos, QColor color)
    : color(color), position(pos)
{
    QRandomGenerator& generator = *QRandomGenerator::system();

    this->speed.setX(static_cast<qreal>(generator.bounded(10,100)) / 1000.0);
    if(generator.generate() % 2 ? true : false){
        this->speed.setX(-1 * this->speed.x());
    }
    this->speed.setY(static_cast<qreal>(generator.bounded(10,100)) / 1000.0);
    if(generator.generate() % 2 ? true : false){
        this->speed.setY(-1 * this->speed.y());
    }
    qDebug() << "speed x=" << this->speed.x() << " y=" << this->speed.y();

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
        scene()->removeItem(this);
    }
}
