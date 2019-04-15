#include "player.h"

#include <QDebug>
#include <QGraphicsScene>
#include "config.h"
#include "laser.hpp"
#include "matrixscene.h"
#include "missile.h"
#include "wreck.h"

const int Player::height = 2;
const int Player::width = 3;

Player::Player(bool upper, QGamepad *gamepad, Bar *healthBar, Bar *powerUp,
               MatrixScene *MScene)
    : time_to_fire(false),
      gamepad(gamepad),
      healthBar(healthBar),
      powerUpBar(powerUp),
      upper(upper),
      life(max_life),
      dead(false),
      power(PowerUp::NONE) {
  if (upper) {
    color = Qt::red;
    setPos(15, 0);
  } else {
    color = Qt::green;
    setPos(15, 16);
  }

  displayHealth();
  sound.setBuffer(*MScene->getSoundBuffer("fire"));

  connect(gamepad, &QGamepad::buttonXChanged, this, [=](bool value) {
    canFire = value;
    startFireTimer(config::duration::time_between_firing);
  });

  connect(powerUp, &Bar::finished, this, [=]() {
    power = PowerUp::NONE;
    sound.setBuffer(
        *static_cast<MatrixScene *>(scene())->getSoundBuffer("fire"));
  });

  // Add hit indicator
  if (upper)
    hitIndicator = new HitIndicator(y(), 28, 3, color.dark());
  else
    hitIndicator = new HitIndicator(y() - 1, 28, 3, color.dark());

  MScene->addItem(hitIndicator);
  hitIndicator->hide();
  hitIndicator->setZValue(-1);

  connect(this, &QGraphicsObject::yChanged, this, [=]() {
    if (upper)
      hitIndicator->moveBy(0, 2);
    else
      hitIndicator->moveBy(0, -2);
  });

  // gainput
  pad = static_cast<gainput::InputDevicePad *>(MScene->manager.GetDevice(
      MScene->manager.CreateDevice<gainput::InputDevicePad>()));
}

QRectF Player::boundingRect() const { return QRectF(0, 0, 3, 2); }

QPainterPath Player::shape() const {
  QPainterPath path;
  if (dead) return path;

  if (upper) {
    path.addRect(0, 0, 3, 1);
    path.addRect(1, 1, 1, 1);
  } else {
    path.addRect(0, 1, 3, 1);
    path.addRect(1, 0, 1, 1);
  }

  return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                   QWidget *) {
  if (dead) return;

  painter->setPen(QPen(color, 1));
  if (upper) {
    painter->drawPoint(1, 1);
    painter->drawLine(0, 0, 2, 0);
  } else {
    painter->drawPoint(1, 0);
    painter->drawLine(0, 1, 2, 1);
  }
}

void Player::advance(int phase) {
  if (dead) return;

  if (phase == 0) {
    if (lookAround(this)) {
      this->hurt(10);
    }
    return;
  }

  if (gamepad->axisLeftX() < -0.4 || gamepad->buttonLeft()) {
    moveLeft();
  } else if (gamepad->axisLeftX() > 0.4 || gamepad->buttonRight()) {
    moveRight();
  }
}

void Player::fire(bool fire) {
  if ((!dead && canFire) || fire) {
    QPointF launch_point = pos() + (upper ? QPointF(1, 2) : QPointF(1, 0));
    switch (power) {
      case PowerUp::DOUBLE_SHOOT:
        scene()->addItem(new Missile(launch_point, color, this, upper));
        startFireTimer(config::duration::time_between_firing_fast);
        break;
      case PowerUp::TRIPLE_SHOOT:
        scene()->addItem(
            new Missile(launch_point + QPointF(-1, 0), color, this, upper));
        scene()->addItem(
            new Missile(launch_point + QPointF(1, 0), color, this, upper));
        scene()->addItem(new Missile(launch_point, color, this, upper));
        startFireTimer(config::duration::time_between_firing);
        break;
      case PowerUp::LASER:
        scene()->addItem(new Laser(this, upper));
        startFireTimer(config::duration::laser);
        break;
      default:
      case PowerUp::NONE:
        scene()->addItem(new Missile(launch_point, color, this, upper));
        startFireTimer(config::duration::time_between_firing);
        break;
    }
    sound.play();
  }
}

void Player::moveLeft() {
  if (pos().x() > 2) {
    moveBy(-1, 0);  // go left
  }
}

void Player::moveRight() {
  if (pos().x() < 27) {
    moveBy(1, 0);  // go right
  }
}

void Player::hurt(size_t loss) {
  if (loss >= life) {
    life = 0;
    displayHealth();
    qDebug() << "Game over!";
    dead = true;
    if (upper) {
      scene()->addItem(new Wreck(this->pos() + QPointF(0, 0), this->color));
      scene()->addItem(new Wreck(this->pos() + QPointF(1, 0), this->color));
      scene()->addItem(new Wreck(this->pos() + QPointF(2, 0), this->color));
      scene()->addItem(new Wreck(this->pos() + QPointF(1, 1), this->color));
    } else {
      scene()->addItem(new Wreck(this->pos() + QPointF(1, 0), this->color));
      scene()->addItem(new Wreck(this->pos() + QPointF(0, 1), this->color));
      scene()->addItem(new Wreck(this->pos() + QPointF(1, 1), this->color));
      scene()->addItem(new Wreck(this->pos() + QPointF(2, 1), this->color));
    }

    // end game with slight delay
    QTimer::singleShot(1500, this, [=]() {
      static_cast<MatrixScene *>(scene())->endGame(upper);
    });
    sound.setBuffer(
        *static_cast<MatrixScene *>(scene())->getSoundBuffer("bangMedium"));
    sound.play();
    return;
  }

  pad->Vibrate(0.5f, 0.5f);
  QTimer::singleShot(250, this, [=]() { pad->Vibrate(0, 0); });
  hitIndicator->show();
  startTimer(100);
  life -= loss;
  displayHealth();

  qDebug() << this << this->life;
}

void Player::applyPowerUp(PowerUp::powerType const pu) {
  if (power == PowerUp::LASER && pu != PowerUp::LASER) return;
  if (dead) return;

  if (pu == PowerUp::HEALTH) {
    life += max_life / 4;
    if (life > max_life) life = max_life;
    displayHealth();
    return;
  }

  power = pu;

  if (power == PowerUp::LASER) {
    powerUpBar->startAnim(config::duration::laser);
    sound.setBuffer(
        *static_cast<MatrixScene *>(scene())->getSoundBuffer("laser"));
  } else {
    powerUpBar->startAnim(config::duration::powerup_effect);
    sound.setBuffer(
        *static_cast<MatrixScene *>(scene())->getSoundBuffer("fire"));
  }
}

void Player::displayHealth() {
  this->healthBar->setValue((float)life / max_life);
}

void Player::startFireTimer(std::chrono::milliseconds time) {
  if (time != time_to_fire && timerStarted) {
    killTimer(fireTimerID);
    fireTimerID = startTimer(time);
    return;
  }

  fireTimerID = startTimer(time);
  timerStarted = true;
}

void Player::hit(Player *p) {
  if (p == this || dead) return;
  qDebug() << "Player hit";
}

void Player::timerEvent(QTimerEvent *event) {
  if (event->timerId() == fireTimerID)
    fire();
  else {
    hitIndicator->hide();
    killTimer(event->timerId());
  }
}
