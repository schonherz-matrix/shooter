#include "asteroid.h"

Asteroid::Asteroid() {
    this->type = QRandomGenerator::global()->bounded(0, 3);
    this->color = Qt::darkGray;
    this->life = Asteroid::MAXLIFE;
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(Qt::NoPen);

    QBrush brush(this->color);
    painter->setBrush(brush);

    if (this->life != 0) {
        if (this->life == 3) {
            painter->drawRect(this->m_x, this->m_y, 2, 2);
        } else if (this->life == 2) {
            if (this->type != 0) {
                painter->drawRect(this->m_x, this->m_y, 1, 1);
            }
            if (this->type != 1) {
                painter->drawRect(this->m_x+1, this->m_y, 1, 1);
            }
            if (this->type != 2) {
                painter->drawRect(this->m_x+1, this->m_y+1, 1, 1);
            }
            if (this->type != 3) {
                painter->drawRect(this->m_x, this->m_y+1, 1, 1);
            }
        } else if (this->life == 1) {
            if (this->type != 0 || this->type != 2) {
                painter->drawRect(this->m_x, this->m_y, 1, 1);
                painter->drawRect(this->m_x+1, this->m_y+1, 1, 1);
            }
            if (this->type != 1 || this->type != 3) {
                painter->drawRect(this->m_x+1, this->m_y, 1, 1);
                painter->drawRect(this->m_x, this->m_y+1, 1, 1);
            }
        }
    }
}

QRectF Asteroid::boundingRect() const {
    return QRectF(this->m_x, this->m_y, 2, 2);
}

QPainterPath Asteroid::shape() const {
    QPainterPath path;
    if (this->life != 0) {
        if (this->life == 3) {
            path.addRect(this->m_x, this->m_y, 2, 2);

        } else if (this->life == 2) {
            if (this->type != 0) {
                path.addRect(this->m_x, this->m_y, 1, 1);
            }
            if (this->type != 1) {
                path.addRect(this->m_x+1, this->m_y, 1, 1);
            }
            if (this->type != 2) {
                path.addRect(this->m_x+1, this->m_y+1, 1, 1);
            }
            if (this->type != 3) {
                path.addRect(this->m_x, this->m_y+1, 1, 1);
            }
        } else if (this->life == 1) {
            if (this->type != 0 || this->type != 2) {
                path.addRect(this->m_x, this->m_y, 1, 1);
                path.addRect(this->m_x+1, this->m_y+1, 1, 1);
            }
            if (this->type != 1 || this->type != 3) {
                path.addRect(this->m_x+1, this->m_y, 1, 1);
                path.addRect(this->m_x, this->m_y+1, 1, 1);
            }
        }
    }

    return path;
}

