#include "PowerUp.h"
#include <QColor>
#include <QPainter>
#include <QRandomGenerator>

PowerUp::PowerUp(){
    QRandomGenerator generator;

    size_t random_type_num = generator.generate() % PowerUp::number_of_types;

    color = PowerUp::types[random_type_num].second;
    power = PowerUp::types[random_type_num].first;

    speed.move_in_y = static_cast<float>(generator.bounded(10,20)) / (generator.bounded(1000));
    speed.move_in_x = static_cast<float>(generator.bounded(10,20)) / (generator.bounded(1000));

    bool dir = generator.generate() % 2 ? true : false;
    if (dir) {
        position.x = 32;
	speed.move_in_x*=-1;
    } else {
        position.x = 0;
    }

    position.y = 13;

    setPos(position.x, position.y);
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
}

void PowerUp::advance(int phase){
	if (phase == 0)
		return;

	moveBy(speed.move_in_x, speed.move_in_y);

	if ( pos().x > 32 || pos().x < 0)
		if( pos().y < 0 || pos().y > 26 )
		{
			delete this;
		}
}

const std::array<std::pair<PowerUp::type, QColor>, PowerUp::number_of_types> PowerUp::types =
{
    std::make_pair(PowerUp::type::HEALTH, Qt::green),
    std::make_pair(PowerUp::type::DOUBLE_SHOOT, Qt::yellow),
    std::make_pair(PowerUp::type::TRIPLE_SHOOT, Qt::red),
    std::make_pair(PowerUp::type::HEALTH, Qt::blue)
};


