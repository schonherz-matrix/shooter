#include "asteroid.h"

Asteroid::Asteroid() {
    this->type = QRandomGenerator::global()->bounded(0, 3);
    this->color = Qt::darkGray;
    this->life = Asteroid::MAXLIFE;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->pieces[i][j] = 1;
        }
    }
}

void Asteroid::hit() {
    if (this->life > 0) {
        if (this->life == 3) {
            this->pieces[2][0] = 0;
            this->pieces[2][3] = 0;
            this->pieces[3][0] = 0;
            this->pieces[3][1] = 0;
            this->pieces[3][3] = 0;
        } else if (this->life == 2) {
            this->pieces[0][0] = 0;
            this->pieces[0][1] = 0;
            this->pieces[0][3] = 0;
        }
        this->life--;
    }
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(this->color, 1));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->pieces[i][j] == 1) {
                painter->drawPoint(i, j);
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
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (this->pieces[i][j] == 1) {
                    path.addRect(i, j, 1, 1);
                }
            }
        }
    }

    return path;
}

