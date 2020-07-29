#include "powerup.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>

#include "matrixscene.h"
#include "missile.h"
#include "player.h"

PowerUp::PowerUp(QGraphicsScene *scene) : anim(this, "pos") {
  size_t random_type_num =
      QRandomGenerator::global()->generate() % PowerUp::number_of_types;

  color = PowerUp::types[random_type_num]
              .second;  // This is going to be the color of the powerup
  power = PowerUp::types[random_type_num]
              .first;  // This is going to be the power of the powerup

  scene->addItem(this);  // Add the powerup to the scene

  int time = QRandomGenerator::global()->bounded(5, 10);

  connect(&anim, &QPropertyAnimation::finished, this, [=]() { remove(); });

  QPointF startPoint;
  QPointF endPoint;

  do {
    startPoint = static_cast<MatrixScene *>(scene)->getRandomEdgePoint();
    endPoint = static_cast<MatrixScene *>(scene)->getRandomEdgePoint();
  } while (
      (startPoint - endPoint).manhattanLength() < 7 ||
      (startPoint - static_cast<MatrixScene *>(scene)->upperPlayer.pos())
              .manhattanLength() < config::distance::player_spawn_asteroide ||
      (startPoint - static_cast<MatrixScene *>(scene)->lowerPlayer.pos())
              .manhattanLength() < config::distance::player_spawn_asteroide);

  anim.setDuration(1000 * time);
  anim.setStartValue(
      static_cast<MatrixScene *>(this->scene())->getRandomEdgePoint());
  anim.setEndValue(
      static_cast<MatrixScene *>(this->scene())->getRandomEdgePoint());
  anim.start();
}

void PowerUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *item,
                    QWidget *widget) {
  Q_UNUSED(item);
  Q_UNUSED(widget);

  painter->setPen(QPen(color, 1));
  painter->drawPoint(0, 0);
}

QRectF PowerUp::boundingRect() const { return QRectF(0, 0, 1, 1); }

QPainterPath PowerUp::shape() const {
  QPainterPath path;
  path.addRect(0, 0, 1, 1);
  return path;
}

const std::array<std::pair<PowerUp::powerType, QColor>,
                 PowerUp::number_of_types>
    PowerUp::types = {
        std::make_pair(PowerUp::powerType::HEALTH, qRgb(200, 150, 150)),
        std::make_pair(PowerUp::powerType::DOUBLE_SHOOT, Qt::yellow),
        std::make_pair(PowerUp::powerType::TRIPLE_SHOOT, qRgb(255, 0, 255)),
        std::make_pair(PowerUp::powerType::LASER, Qt::blue)};

void PowerUp::hit(Player *attacker) {
  qDebug() << "PowerUp hit";

  attacker->applyPowerUp(this->power);

  remove();
}
