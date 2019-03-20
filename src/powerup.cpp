#include "powerup.h"
#include <QColor>
#include <QPainter>
#include <QRandomGenerator>

PowerUp::PowerUp(){
    QRandomGenerator generator;

    size_t random_type_num = generator.generate() % PowerUp::number_of_types;

    color = PowerUp::types[random_type_num].second;
    power = PowerUp::types[random_type_num].first;

    speed.ry() = static_cast<qreal>(generator.bounded(10,20)) / (generator.bounded(1000));
    speed.rx() = static_cast<qreal>(generator.bounded(10,20)) / (generator.bounded(1000));

    qreal x, y;

    bool dir = generator.generate() % 2 ? true : false;
    if (dir) {
        x = 32;
	speed.rx()*=-1;
    } else 
        x = 0;

    y = 13;

    setPos(x, y);
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

    if ( pos().x() > 32 || pos().x() < 0)
        if( pos().y() < 0 || pos().y() > 26 )
		{
			delete this;
        }
}

void PowerUp::kill()
{
    //TODO: implement
    //called when powerup needs to die; e.g.: used up
}

const std::array<std::pair<PowerUp::type, QColor>, PowerUp::number_of_types> PowerUp::types =
{
    std::make_pair(PowerUp::type::HEALTH, Qt::green),
    std::make_pair(PowerUp::type::DOUBLE_SHOOT, Qt::yellow),
    std::make_pair(PowerUp::type::TRIPLE_SHOOT, Qt::red),
    std::make_pair(PowerUp::type::HEALTH, Qt::blue)
};


const PowerUp::type PowerUp::getPower() const{
	return power;
}
