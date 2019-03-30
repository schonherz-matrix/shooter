#include "powerup.h"

#include <QColor>
#include <QPainter>
#include <QRandomGenerator>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsScene>
#include "missile.h"
#include "player.h"

PowerUp::PowerUp(QGraphicsScene* scene) :
    anim(this, "pos")
{
    size_t random_type_num = QRandomGenerator::global()->generate() % PowerUp::number_of_types;

    color = PowerUp::types[random_type_num].second; //This is going to be the color of the powerup
    power = PowerUp::types[random_type_num].first;  //This is going to be the power of the powerup

    scene->addItem(this); //Add the powerup to the scene

    int side = QRandomGenerator::global()->bounded(0, 4);
    int startX, startY, endX, endY;

    switch (side) {
    case 0: // left
        startX = -5;
        endX = 32;
        startY = QRandomGenerator::global()->bounded(0, 27);
        endY = QRandomGenerator::global()->bounded(0, 27);
        break;
    case 1: // right
        startX = 32;
        endX = -5;
        startY = QRandomGenerator::global()->bounded(0, 27);
        endY = QRandomGenerator::global()->bounded(0, 27);
        break;
    case 2: // up
        startY = 0;
        endY = 28;
        startX = QRandomGenerator::global()->bounded(0, 33);
        endX = QRandomGenerator::global()->bounded(0, 33);
        break;
    case 3: // down
        startY = 26;
        endY = -5;
        startX = QRandomGenerator::global()->bounded(0, 33);
        endX = QRandomGenerator::global()->bounded(0, 33);
        break;
    }

    int time = QRandomGenerator::global()->bounded(5, 10);

    connect(&anim, &QPropertyAnimation::finished, this, [=](){
        remove();
    });

    anim.setDuration(1000 * time);
    anim.setStartValue(QPointF(startX, startY));
    anim.setEndValue(QPointF(endX, endY));
    anim.start();
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

const std::array<std::pair<PowerUp::powerType, QColor>, PowerUp::number_of_types> PowerUp::types =
{
    std::make_pair(PowerUp::powerType::HEALTH, Qt::green),
    std::make_pair(PowerUp::powerType::DOUBLE_SHOOT, Qt::yellow),
    std::make_pair(PowerUp::powerType::TRIPLE_SHOOT, Qt::red),
    std::make_pair(PowerUp::powerType::LASER, Qt::blue)
};

void PowerUp::hit(Player *attacker)
{
    qDebug() << "PowerUp hit";

    attacker->applyPowerUp(this->power);

    remove();
}
