#include "asteroid.h"

#include <QGraphicsScene>
#include <QDebug>
#include "missile.h"
#include <QMediaPlayer>

static QMediaPlayer p;

Asteroid::Asteroid(QGraphicsScene* scene) {
    QRandomGenerator& generator = *QRandomGenerator::system();

    this->look = QRandomGenerator::global()->bounded(0, 3);
    this->color = Qt::darkGray;
    this->life = Asteroid::MAXLIFE;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->pieces[i][j] = 1;
        }
    }

    this->speed.move_in_y = static_cast<float>(generator.bounded(10,20)) / (generator.bounded(1000));
    if(generator.generate() % 2 ? true : false){
        this->speed.move_in_y*=-1;
    }

    this->speed.move_in_x = static_cast<float>(generator.bounded(10,20)) / (generator.bounded(1000));

    bool dir = generator.generate() % 2 ? true : false;
    if (dir) {
        position.x = 32;
        speed.move_in_x*=-1;
    } else {
        position.x = 0;
    }

    position.y = 13;

    scene->addItem(this);

    setPos(position.x, position.y);
}

void Asteroid::paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) {
    Q_UNUSED(item);
    Q_UNUSED(widget);

    painter->setPen(QPen(this->color, 1));

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->pieces[i][j] == 1) {
                painter->drawPoint(i, j);
            }
        }
    }
}

QRectF Asteroid::boundingRect() const {
    return QRectF(0, 0, 4, 4);
}

QPainterPath Asteroid::shape() const {
    QPainterPath path;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (this->pieces[i][j] == 1) {
                path.addRect(i, j, 1, 1);
            }
        }
    }

    return path;
}

void Asteroid::advance(int phase) {
    if (phase == 0)
        return;

    this->moveBy(speed.move_in_x, speed.move_in_y);

    if ( this->pos().x() > 32 || this->pos().x() < 0) {
        if( this->pos().y() < 0 || this->pos().y() > 26 ) {
            remove();
        }
    }
}


void Asteroid::hit(Player*)
{
    qDebug() << "Asteroid hit";

    if(life == 1) {
        remove();
        return;
    }

    if (this->life == Asteroid::MAXLIFE) {
        this->pieces[2][0] = 0;
        this->pieces[2][3] = 0;
        this->pieces[3][0] = 0;
        this->pieces[3][1] = 0;
        this->pieces[3][3] = 0;
        this->pieces[0][0] = 0;
        this->pieces[0][1] = 0;
        this->pieces[0][3] = 0;
    }

    life--;
    p.setMedia(QUrl::fromLocalFile("data/sounds/bangLarge.wav"));
    p.play();
}
