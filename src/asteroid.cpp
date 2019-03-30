#include "asteroid.h"

#include <QGraphicsScene>
#include <QDebug>
#include "missile.h"

Asteroid::Asteroid(QGraphicsScene* scene)
    : p(nullptr, QMediaPlayer::LowLatency),
      anim(this, "pos")
{
    this->look = QRandomGenerator::global()->bounded(0, 3);
    this->color = Qt::darkGray;
    this->life = Asteroid::MAXLIFE;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->pieces[i][j] = 1;
        }
    }

    scene->addItem(this);
    p.setMedia(QUrl::fromLocalFile("data/sounds/bangLarge.wav"));

    int side = QRandomGenerator::global()->bounded(0, 4);
    int startX, startY, endX, endY;

    switch (side) {
    case 0: // left
        startX = -5;
        endX = 32;
        startY = QRandomGenerator::global()->bounded(0, 27);
        endY = QRandomGenerator::global()->bounded(0, 27);
        break;
    case 1: // right
        startX = 32;
        endX = -5;
        startY = QRandomGenerator::global()->bounded(0, 27);
        endY = QRandomGenerator::global()->bounded(0, 27);
        break;
    case 2: // up
        startY = 0;
        endY = 28;
        startX = QRandomGenerator::global()->bounded(0, 33);
        endX = QRandomGenerator::global()->bounded(0, 33);
        break;
    case 3: // down
        startY = 26;
        endY = -5;
        startX = QRandomGenerator::global()->bounded(0, 33);
        endX = QRandomGenerator::global()->bounded(0, 33);
        break;
    }

    int time = QRandomGenerator::global()->bounded(5, 10);

    connect(&anim, &QPropertyAnimation::finished, this, [=](){
        remove();
    });

    anim.setDuration(1000 * time);
    anim.setStartValue(QPointF(startX, startY));
    anim.setEndValue(QPointF(endX, endY));
    anim.start();
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
    return QRectF(0, 0, 4, 4);
}

QPainterPath Asteroid::shape() const {
    QPainterPath path;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->pieces[i][j] == 1) {
                path.addRect(i, j, 1, 1);
            }
        }
    }

    return path;
}

void Asteroid::hit(Player*)
{
    qDebug() << "Asteroid hit";

    if(life == 1) {
        remove();
        return;
    }

    if (this->life == Asteroid::MAXLIFE) {
        this->pieces[2][0] = 0;
        this->pieces[2][3] = 0;
        this->pieces[3][0] = 0;
        this->pieces[3][1] = 0;
        this->pieces[3][3] = 0;
        this->pieces[0][0] = 0;
        this->pieces[0][1] = 0;
        this->pieces[0][3] = 0;
    }

    life--;
    p.play();
}
