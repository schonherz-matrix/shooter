#include "asteroid.h"

Asteroid::Asteroid() {
    this->type = QRandomGenerator::global()->bounded(0, 3);
    this->color = Qt::darkGray;
    this->life = Asteroid::MAXLIFE;
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(this->color, 1));

    if (this->life != 0) {
        if (this->life == 3) {
            painter->drawRect(0, 0, 2, 2);
        } else if (this->life == 2) {
            if (this->type != 0) {
                painter->drawPoint(1, 1);
            }
            if (this->type != 1) {
                painter->drawRect(1, 0, 1, 1);
            }
            if (this->type != 2) {
                painter->drawRect(1, 1, 1, 1);
            }
            if (this->type != 3) {
                painter->drawRect(0, 0, 1, 1);
            }
        } else if (this->life == 1) {
            if (this->type != 0 || this->type != 2) {
                painter->drawRect(0, 0, 1, 1);
                painter->drawRect(1, 1, 1, 1);
            }
            if (this->type != 1 || this->type != 3) {
                painter->drawRect(1, 0, 1, 1);
                painter->drawRect(0, 1, 1, 1);
            }
        }
    }
}

QRectF Asteroid::boundingRect() const {
    return QRectF(0, 0, 2, 2);
}

QPainterPath Asteroid::shape() const {
    QPainterPath path;
    if (this->life != 0) {
        if (this->life == 3) {
            path.addRect(0, 0, 2, 2);

        } else if (this->life == 2) {
            if (this->type != 0) {
                path.addRect(0, 0, 1, 1);
            }
            if (this->type != 1) {
                path.addRect(1, 0, 1, 1);
            }
            if (this->type != 2) {
                path.addRect(1, 1, 1, 1);
            }
            if (this->type != 3) {
                path.addRect(0, 1, 1, 1);
            }
        } else if (this->life == 1) {
            if (this->type != 0 || this->type != 2) {
                path.addRect(0, 0, 1, 1);
                path.addRect(1, 1, 1, 1);
            }
            if (this->type != 1 || this->type != 3) {
                path.addRect(1, 0, 1, 1);
                path.addRect(0, 1, 1, 1);
            }
        }
    }

    return path;
}

