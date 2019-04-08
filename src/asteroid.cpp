#include "asteroid.h"

#include <QGraphicsScene>
#include <QDebug>
#include "missile.h"
#include "matrixscene.h"

bool inRange(qreal low, qreal high, qreal x)
{
    return  ((x-low) <= (high-low));
}

Asteroid::Asteroid(MatrixScene* MScene, QVector<QPointF> players)
    : anim(this, "pos")
{
    this->life = Asteroid::MAXLIFE;
    this->look = static_cast<AsteroidType>(QRandomGenerator::global()->bounded(0, 3));

    switch (this->look) {
    case AsteroidType::SMALL :
        sound.setBuffer(*MScene->getSoundBuffer("bangSmall"));
        pixmapItem.setPixmap(QPixmap("data/asteroids/small-1.png"));
        break;
    case AsteroidType::MEDIUM :
        sound.setBuffer(*MScene->getSoundBuffer("bangMedium"));
        pixmapItem.setPixmap(QPixmap("data/asteroids/medium-1.png"));
        break;
    case AsteroidType::LARGE :
        sound.setBuffer(*MScene->getSoundBuffer("bangLarge"));
        pixmapItem.setPixmap(QPixmap("data/asteroids/large-1.png"));
        break;
    }

    MScene->addItem(this);

    int side = QRandomGenerator::global()->bounded(0, 2);
    int startX, startY, endX, endY;

    switch (side) {
    case 0: // left
        startX = -5;
        endX = 37;
        startY = QRandomGenerator::global()->bounded(5, 25);
        endY = QRandomGenerator::global()->bounded(5, 25);
        break;
    case 1: // right
        startX = 37;
        endX = -5;
        startY = QRandomGenerator::global()->bounded(5, 25);
        endY = QRandomGenerator::global()->bounded(5, 25);
        break;
    }

    int time = QRandomGenerator::global()->bounded(5, 10);

    connect(&anim, &QPropertyAnimation::finished, this, [=](){
        remove();
    });

    if(inRange(players[0].y()-5, players[0].y()+5, startY))
        startY += 5;

    if(inRange(players[1].y()-5, players[1].y()+5, startY))
        startY -= 5;

    anim.setDuration(1000 * time);
    anim.setStartValue(QPointF(startX, startY));
    anim.setEndValue(QPointF(endX, endY));
    anim.start();
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    pixmapItem.paint(painter, item, widget);
}

QRectF Asteroid::boundingRect() const {
    return this->pixmapItem.boundingRect();
}

QPainterPath Asteroid::shape() const {
    return this->pixmapItem.shape();
}

void Asteroid::hit(Player*)
{
    qDebug() << "Asteroid hit";

    switch (this->look) {
    case AsteroidType::SMALL :
        pixmapItem.setPixmap(QPixmap("data/asteroids/small-2.png"));
        break;
    case AsteroidType::MEDIUM :
        pixmapItem.setPixmap(QPixmap("data/asteroids/medium-2.png"));
        break;
    case AsteroidType::LARGE :
        pixmapItem.setPixmap(QPixmap("data/asteroids/large-2.png"));
        break;
    }

    if(life > 0) {
        sound.play();
        life--;
    }
}

bool Asteroid::removeAble()
{
    return !life;
}

bool Asteroid::deleteAble()
{
    return sound.getStatus() == sound.Stopped;
}
