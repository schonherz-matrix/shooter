#include "powerup.h"

#include <QColor>
#include <QPainter>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsScene>
#include "missile.h"
#include "player.h"

PowerUp::PowerUp(QGraphicsScene* scene){
    QRandomGenerator& random_generator = *QRandomGenerator::system();

    size_t random_type_num = random_generator.generate() % PowerUp::number_of_types;

    color = PowerUp::types[random_type_num].second; //This is going to be the color of the powerup
    power = PowerUp::types[random_type_num].first;  //This is going to be the power of the powerup

    //Generate random speed
    speed.ry() = static_cast<qreal>(random_generator.bounded(10,20)) / (random_generator.bounded(1000));
    if(random_generator.generate() % 2 ? true : false){
        this->speed.ry()*=-1;
    }
    speed.rx() = static_cast<qreal>(random_generator.bounded(10,20)) / (random_generator.bounded(1000));

    qreal x, y; //The coordiante where to of spawn

    bool dir = random_generator.generate() % 2 ? true : false;
    if (dir) { //If the powerup goes from right to left
        x = 32;
        speed.rx()*=-1;
    } else 
        x = 0;

    y = random_generator.bounded(10, 20); //TODO justify

    scene->addItem(this); //Add the powerup to the scene
    setPos(x, y); //set powerup position on the scene
}

void PowerUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(color, 1));
    painter->drawPoint(0,0);
}

QRectF PowerUp::boundingRect() const{
    return QRectF(0,0,1,1);
}

QPainterPath PowerUp::shape() const{
    QPainterPath path;
    path.addRect(0,0,1,1);
    return path;
}

void PowerUp::advance(int phase){
	if (phase == 0)
		return;

	setPos(pos() + speed);

    if (
         pos().x() > 32 || pos().x() < 0  //If we are out of map horizontally
           ||
         pos().y() < 0 || pos().y() > 26  //If we are out of map vertically
       ){
            remove(); //Remove powerUp from map, and free memory
            return;
        }
}

const std::array<std::pair<PowerUp::powerType, QColor>, PowerUp::number_of_types> PowerUp::types =
{
    std::make_pair(PowerUp::powerType::HEALTH, Qt::green),
    std::make_pair(PowerUp::powerType::DOUBLE_SHOOT, Qt::yellow),
    std::make_pair(PowerUp::powerType::TRIPLE_SHOOT, Qt::red),
    std::make_pair(PowerUp::powerType::HEALTH, Qt::blue)
};

void PowerUp::hit(Player *attacker)
{
    qDebug() << "PowerUp hit";

    attacker->applyPowerUp(this->power);

    remove();
}
