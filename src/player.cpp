#include "player.h"

#include <QDebug>
#include <QGraphicsScene>
#include "missile.h"

Player::Player(bool upper, QGamepad *gamepad, Bar *healthBar, Bar *powerUp)
    : gamepad(gamepad),
      healthBar(healthBar),
      powerUp(powerUp),
      upper(upper),
      life(max_life),
      power(PowerUp::NONE){
  if (upper) {
    // lightpink	#FFB6C1	rgb(255,182,193)
    color = QColor(255, 82, 193);
    setPos(15, 0);
  } else {
    color = Qt::green;
    setPos(15, 24);
  }
}

QRectF Player::boundingRect() const { return QRectF(0, 0, 3, 2); }

QPainterPath Player::shape() const {
  QPainterPath path;

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
  if (phase == 0) {
    if (time_to_fire) time_to_fire--;
    if (time_from_power) time_from_power--;
    if (! time_from_power)
        power = PowerUp::NONE;

    lookAround(this);
    return;
  }

  if (gamepad->buttonLeft() && !gamepad->buttonRight() && pos().x() > 2) {
    // go left
    moveBy(-1, 0);
  } else if (!gamepad->buttonLeft() && gamepad->buttonRight() && pos().x() < (30-3)) {
    // go right
    moveBy(1, 0);
  } else if (!gamepad->buttonL1() && time_to_fire == 0) {
    // FIRE
    QPointF launch_point;

    switch(power){
        case PowerUp::DOUBLE_SHOOT:
            launch_point = {pos().x()    , pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point, color, this, upper));

            launch_point = {pos().x() + 2, pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point, color, this, upper));
			time_to_fire = 300; 
		    break;
        case PowerUp::TRIPLE_SHOOT:
            launch_point = {pos().x()    , pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point, color, this, upper));

            launch_point = {pos().x() + 1, pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point , color, this, upper));

            launch_point = {pos().x() + 2, pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point , color, this, upper));
			time_to_fire = 300; 
		    break;

        case PowerUp::LASER: //TODO FIX, this is not good | these missiles should be faster than others
            launch_point  = {pos().x() + 1, pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point , color, this, upper));
		    time_to_fire = 10; 
            break;
        default:
        case PowerUp::NONE:
            launch_point  = {pos().x() + 1, pos().y() + (upper ? -1 : 1)};
            scene()->addItem(new Missile(launch_point , color, this, upper));
            time_to_fire = 300;
            break;
    }
  }
}


void Player::hurt(size_t loss) {
  if (loss >= life) {
    // TODO: kill, end game
    return;
  }
  life -= loss;
}

void Player::applyPowerUp(PowerUp::powerType const pu)
{
    if(pu == PowerUp::HEALTH){
	    //TODO increase health and 
	    return;
    }

    time_from_power = 10000;
    
    power = pu;
}


void Player::hit(Player*)
{
}
