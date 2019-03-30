#include "asteroid.h"

#include <QGraphicsScene>
#include <QDebug>
#include "missile.h"

Asteroid::Asteroid(QGraphicsScene* scene)
    : p(nullptr, QMediaPlayer::LowLatency),
      anim(this, "pos")
{
    this->life = Asteroid::MAXLIFE;
    this->type = static_cast<AsteroidType>(QRandomGenerator::global()->bounded(0, 3));

    switch (this->type) {
    case AsteroidType::SMALL :
        p.setMedia(QUrl::fromLocalFile("data/sounds/bangSmall.wav"));
        pixmapItem.setPixmap(QPixmap("data/asteroids/small-1.png"));
        break;
    case AsteroidType::MEDIUM :
        p.setMedia(QUrl::fromLocalFile("data/sounds/bangMedium.wav"));
        pixmapItem.setPixmap(QPixmap("data/asteroids/medium-1.png"));
        break;
    case AsteroidType::LARGE :
        p.setMedia(QUrl::fromLocalFile("data/sounds/bangLarge.wav"));
        pixmapItem.setPixmap(QPixmap("data/asteroids/large-1.png"));
        break;
    }

    scene->addItem(this);

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

    if(life == 1) {
        remove();
        return;
    }

    switch (this->type) {
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

    life--;
    p.play();
}
