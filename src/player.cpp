#include "player.h"
#include "config.h"
#include <QDebug>
#include <QGraphicsScene>
#include "missile.h"
#include "wreck.h"

Player::Player(bool upper, QGamepad *gamepad, Bar *healthBar, Bar *powerUp)
    : gamepad(gamepad),
      healthBar(healthBar),
      powerUp(powerUp),
      upper(upper),
      life(max_life),
      time_to_fire(0),
      p(nullptr, QMediaPlayer::LowLatency),
      power(PowerUp::NONE),
      time_from_power(0),
      dead(false)

{
  if (upper) {
    color = Qt::red;
    setPos(15, 0);
  } else {
    color = Qt::green;
    setPos(15, 24);
  }
  displayHealth();
  displayPowerUp();
  p.setMedia(QUrl::fromLocalFile("data/sounds/fire.wav"));
}

QRectF Player::boundingRect() const { return QRectF(0, 0, 3, 2); }

QPainterPath Player::shape() const {
  QPainterPath path;
  if (dead)
    return path;

  if (upper) {
    path.addRect(0, 0, 3, 1);
  } else {
    path.addRect(0, 1, 3, 1);
  }

  return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
  Q_UNUSED(option);
  Q_UNUSED(widget);
  if (dead)
    return;

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
  if (dead)
    return;

  if (phase == 0) {
    if (time_to_fire) time_to_fire--;
    if (time_from_power) time_from_power--;
    if (! time_from_power)
        power = PowerUp::NONE;

    if (lookAround(this)){
        this->hurt(10);
    }
    return;
  }

  if ((gamepad->axisLeftX() < -0.4 || gamepad->buttonLeft() )&& pos().x() > 2){
    moveBy(-1, 0); // go left
  } else if ((gamepad->axisLeftX() > 0.4 || gamepad->buttonRight()) && pos().x() < 27){
    moveBy(1, 0); // go right
  }

  if ( gamepad->buttonX() && time_to_fire == 0) { // FIRE
    QPointF launch_point = pos() + (upper ? QPointF(1, 2) : QPointF(1, 0));;

    switch(power){
        case PowerUp::TRIPLE_SHOOT:
            scene()->addItem(new Missile(launch_point                 , color, this, upper));
            break;
        case PowerUp::DOUBLE_SHOOT:
            scene()->addItem(new Missile(launch_point + QPointF(-1, 0), color, this, upper));
            scene()->addItem(new Missile(launch_point + QPointF( 1, 0), color, this, upper));
            scene()->addItem(new Missile(launch_point, color, this, upper));
            time_to_fire = config::duration::time_between_fireing;
            break;
        case PowerUp::LASER: //TODO FIX, this is not good | these missiles should be faster than others
            scene()->addItem(new Missile(launch_point , color, this, upper));
            time_to_fire = config::duration::laser_spacing;
            break;
        default:
        case PowerUp::NONE:
            scene()->addItem(new Missile(launch_point , color, this, upper));
            time_to_fire = config::duration::time_between_fireing;
            break;
    }
    p.play();
  }
  displayPowerUp();
}


void Player::hurt(size_t loss) {
  if (loss >= life) {
      life = 0;
      displayHealth();
      qDebug() << "Game over!";
      dead = true;
      if (upper) {
          scene()->addItem(new Wreck(this->pos() + QPointF(0,0), this->color));
          scene()->addItem(new Wreck(this->pos() + QPointF(1,0), this->color));
          scene()->addItem(new Wreck(this->pos() + QPointF(2,0), this->color));
          scene()->addItem(new Wreck(this->pos() + QPointF(1,1), this->color));
      }
      else {
          scene()->addItem(new Wreck(this->pos() + QPointF(1,0), this->color));
          scene()->addItem(new Wreck(this->pos() + QPointF(0,1), this->color));
          scene()->addItem(new Wreck(this->pos() + QPointF(1,1), this->color));
          scene()->addItem(new Wreck(this->pos() + QPointF(2,1), this->color));
      }
      // TODO: kill, end game
      return;
  }
  life -= loss;
  displayHealth();

  qDebug() << this << this->life;
}

void Player::applyPowerUp(PowerUp::powerType const pu)
{
    if (dead)
      return;

    if(pu == PowerUp::HEALTH){
        if (life > 0)
        {
            life = max_life;
            displayHealth();
            //TODO increase health and
        }
	    return;
    }

    time_from_power = config::duration::powerup_effect;
    power = pu;
    displayPowerUp();
}

void Player::displayHealth()
{
    this->healthBar->setValue((float)life / max_life);
}

void Player::displayPowerUp()
{
    this->powerUp->setValue((float)time_from_power / config::duration::powerup_effect);
}

void Player::hit(Player* p)
{
    if (p == this || dead)
        return;
    qDebug() << "Player hit";
    this->hurt(10);
}
