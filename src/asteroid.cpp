#include "asteroid.h"

#include <QDebug>
#include <QGraphicsScene>
#include <cmath>

#include "matrixscene.h"
#include "missile.h"
#include "player.h"

Asteroid::Asteroid(MatrixScene *MScene) : anim(this, "pos") {
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
  auto width = pixmapItem.boundingRect().width();

  qDebug() << height << width;

  do {
    start = MScene->getRandomEdgePoint() - QPointF{width, height};
    end = MScene->getRandomEdgePoint();
  } while (
      ((start - MScene->upperPlayer.pos()).manhattanLength()) <
          (config::distance::player_spawn_asteroide + std::max(height, width) +
           std::max(Player::width, Player::height)) ||
      ((start - MScene->lowerPlayer.pos()).manhattanLength()) <
          (config::distance::player_spawn_asteroide + std::max(height, width) +
           std::max(Player::width, Player::height)) ||
      std::abs((end - start).y()) <
          (config::distance::asteroide_evelation + height));

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
