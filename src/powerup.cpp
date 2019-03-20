#include "powerup.h"
#include <QColor>
#include <QPainter>
#include <QRandomGenerator>

powerup::powerup(){
    QRandomGenerator generator;

    size_t random_type_num = generator.QRandomGenerator::generate() % powerup::number_of_types;

    color = powerup::types[random_type_num].second;
    power = powerup::types[random_type_num].first;

    int random_move_direction_temp = ;
    double random_move_direction = (random_move_direction_temp) / ;

    speed.move_in_y = 1.0 * generator.QRandomGenerator::bounded(-10,10) / (generator.QRandomGenerator::bounded(1000));
    speed.move_in_x = 1.0 * generator.QRandomGenerator::bounded(-10,10) / (generator.QRandomGenerator::bounded(1000));

    if (speed.move_in_x < 0) {
        position.x = 32;
    } else {
        position.x = 0;
    }

    position.y = 13;

    setPos(position.x, position.y);
}

void powerup::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget){
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(color, 1));
    painter->drawPoint(0,0);
}

QRectF powerup::boundingRect() const{
    return QRectF(0,0,1,1);
}

QPainterPath powerup::shape() const{
    QPainterPath path;
    path.addRect(0,0,1,1);
}

const std::array<std::pair<powerup::type, QColor>, powerup::number_of_types> powerup::types =
{
    std::make_pair(powerup::type::HEALTH, Qt::green),
    std::make_pair(powerup::type::DOUBLE_SHOOT, Qt::yellow),
    std::make_pair(powerup::type::TRIPLE_SHOOT, Qt::red),
    std::make_pair(powerup::type::HEALTH, Qt::blue)
};


