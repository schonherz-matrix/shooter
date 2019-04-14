#include "asteroid.h"

#include <QDebug>
#include <QGraphicsScene>
#include "matrixscene.h"
#include "missile.h"
#include <math.h>
#include "player.h"

QPointF getRandomEdgePoint(){
    using config::mapWidth;
    using config::mapHeight;

    QPointF ret;

    qreal l1 = QRandomGenerator::global()->bounded(static_cast<quint32>((mapWidth + mapHeight)/2));

    if(l1 > (mapWidth/2.0)){
        ret.setX(mapWidth/2.0);
        ret.setY(l1 - (mapWidth/2.0));
    }
    else{
        ret.setX(l1);
        ret.setY(mapHeight/2.0);
    }

    if(QRandomGenerator::global()->bounded(0, 2) == 1)
        ret.ry()*=-1;

    if(QRandomGenerator::global()->bounded(0, 2) == 1)
        ret.rx()*=-1;

    ret+=QPointF{config::mapWidth/2.0, config::mapHeight/2.0};

    qDebug() << ret;

    return ret;
}

Asteroid::Asteroid(MatrixScene *MScene, QVector<QPointF> players)
    : anim(this, "pos") {
  this->life = Asteroid::MAXLIFE;
  this->look =
      static_cast<AsteroidType>(QRandomGenerator::global()->bounded(0, 3));

  switch (this->look) {
    case AsteroidType::SMALL:
      sound.setBuffer(*MScene->getSoundBuffer("bangSmall"));
      pixmapItem.setPixmap(QPixmap("data/asteroids/small-1.png"));
      break;
    case AsteroidType::MEDIUM:
      sound.setBuffer(*MScene->getSoundBuffer("bangMedium"));
      pixmapItem.setPixmap(QPixmap("data/asteroids/medium-1.png"));
      break;
    case AsteroidType::LARGE:
      sound.setBuffer(*MScene->getSoundBuffer("bangLarge"));
      pixmapItem.setPixmap(QPixmap("data/asteroids/large-1.png"));
      break;
  }

  MScene->addItem(this);

  QPointF start;
  QPointF end;

  auto height = pixmapItem.boundingRect().height();
  auto width  = pixmapItem.boundingRect().width();

  qDebug() << height << width;

  do{
      start = getRandomEdgePoint() - QPointF{width, height};
        end = getRandomEdgePoint();
  } while (
            (start-players[0]).manhattanLength() < (config::distance::player_spawn_asteroide + std::max(height, width) + std::max(Player::width, Player::height))
           ||
            (start-players[1]).manhattanLength() < (config::distance::player_spawn_asteroide + std::max(height, width) + std::max(Player::width, Player::height))
           ||
            std::abs((end-start).y()) < (config::distance::asteroide_evelation + height)
           );

  int time = QRandomGenerator::global()->bounded(5, 10);

  connect(&anim, &QPropertyAnimation::finished, this, [=]() { remove(); });

  anim.setDuration(1000 * time);
  anim.setStartValue(start);
  anim.setEndValue(end);
  anim.start();
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
                     QWidget *widget) {
  pixmapItem.paint(painter, item, widget);
}

QRectF Asteroid::boundingRect() const {
  return this->pixmapItem.boundingRect();
}

QPainterPath Asteroid::shape() const { return this->pixmapItem.shape(); }

void Asteroid::hit(Player *) {
  qDebug() << "Asteroid hit";

  switch (this->look) {
    case AsteroidType::SMALL:
      pixmapItem.setPixmap(QPixmap("data/asteroids/small-2.png"));
      break;
    case AsteroidType::MEDIUM:
      pixmapItem.setPixmap(QPixmap("data/asteroids/medium-2.png"));
      break;
    case AsteroidType::LARGE:
      pixmapItem.setPixmap(QPixmap("data/asteroids/large-2.png"));
      break;
  }

  if (life > 0) {
    sound.play();
    life--;
  }
}

bool Asteroid::removeAble() { return !life; }

bool Asteroid::deleteAble() { return sound.getStatus() == sound.Stopped; }
