#include "matrixscene.h"

#include <QRandomGenerator>
#include "bar.h"
#include "config.h"
#include <QDir>

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(32, 26, QImage::Format_RGB888),
      painter(&frame),
      player1HPBar(Qt::green, 1),
      player2HPBar(Qt::red, 1),
      player1PWBar(Qt::yellow, 0),
      player2PWBar(Qt::yellow, 0),
      counter_to_shrink(0),
      lowerBorder(false),
      upperBorder(true)
    {
    // set BG
    setBackgroundBrush(Qt::black);

    // setSize
    setSceneRect(0, 0, 32, 26);

    auto gamepads = QGamepadManager::instance()->connectedGamepads();
    if (gamepads.isEmpty() /*|| gamepads.size() < 2*/) {
        qDebug() << "Did not find any connected gamepads";
        /*
        QGraphicsTextItem* felk_jel = new QGraphicsTextItem("?");
        felk_jel->setDefaultTextColor(Qt::red);
        felk_jel->setFont(QFont("Comic Sans", 18));
        felk_jel->setPos(0,0);
        addItem(felk_jel);
        return;
        */
    }

    // init Timer
    timerID = startTimer(1000 / config::gameSpeed::fps);

    // load sound files
    QDir dir("data/sounds");
    QListIterator<QFileInfo> it(dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot));
    while (it.hasNext()) {
        QFileInfo file = it.next();
        sf::SoundBuffer* buffer = new sf::SoundBuffer;
        buffer->loadFromFile(file.filePath().toStdString());
        buffers[file.baseName()] = buffer;
    }

    // init Map
    // set pos
    player1HPBar.setPos(0, 0);
    player1PWBar.setPos(1, 0);
    player2HPBar.setPos(31, 0);
    player2PWBar.setPos(30, 0);

    // add bars
    addItem(&player1HPBar);
    addItem(&player2HPBar);
    addItem(&player1PWBar);
    addItem(&player2PWBar);

    upperPlayer = new Player(true, new QGamepad(1, this), &player2HPBar, &player2PWBar, this);
    lowerPlayer = new Player(false, new QGamepad(0, this), &player1HPBar, &player1PWBar, this);
    addItem(upperPlayer);
    addItem(lowerPlayer);

    // add borders
    addItem(&lowerBorder);
    addItem(&upperBorder);
}

sf::SoundBuffer* MatrixScene::getSoundBuffer(QString name)
{
    return buffers[name];
}

void MatrixScene::endGame(bool upper)
{
    gameOver = true;
    addRect(0, 0, 32, 26, Qt::NoPen, (upper) ? Qt::green : Qt::red);
    auto text = addText((upper) ? "P1" : "P2");
    text->setPos(7, -5);
    auto won = addText("WON!");
    won->setPos(-1, 5);
}

void MatrixScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        lowerPlayer->moveLeft();
        break;
    case Qt::Key_Right:
        lowerPlayer->moveRight();
        break;
    case Qt::Key_A:
        upperPlayer->moveLeft();
        break;
    case Qt::Key_D:
        upperPlayer->moveRight();
        break;
    case Qt::Key_Control:
        lowerPlayer->fire(true);
        break;
    case Qt::Key_Space:
        upperPlayer->fire(true);
        break;
    default:
        break;
    }
}

// main event loop
// advance_and_gc()
void MatrixScene::timerEvent(QTimerEvent *event)
{
    if (!gameOver) {
        //Spawn new asteroide
        if ( QRandomGenerator::system()->bounded(config::chance::spawn_asteroide) == 0) {
            QVector<QPointF> players;
            players.append(upperPlayer->pos());
            players.append(lowerPlayer->pos());
            new Asteroid(this, players);
        }
        //Spawn new powerup
            if ( QRandomGenerator::system()->bounded(config::chance::spawn_powerup) == 0)
                new PowerUp(this);

        //Move players closer
            counter_to_shrink++;
            if ( counter_to_shrink == config::gameSpeed::time_between_shrink ){
                if (upperPlayer->pos().y() < (frame.height() - 6) / 2)
                {
                    upperPlayer->moveBy(0,  2);
                    upperBorder.moveBy(0, 2);
                    lowerPlayer->moveBy(0, -2);
                    lowerBorder.moveBy(0, -2);
                }
                counter_to_shrink=0;
            }

        //Advance
        const auto items_before_advance = QGraphicsScene::items();

        //The basic 'advance' function  TODO call QGraphicsScene::advance() instead???
        for (int i = 0; i < 2; ++i) {
            const auto items_ = items();

            upperPlayer->advance(i); //alternative soultion; players do lookAround in phase 1, others in two
            lowerPlayer->advance(i);

            for (QGraphicsItem *item : items_){
                if(item == upperPlayer || item == lowerPlayer)
                    continue;
                item->advance(i);
            }
        }

        //Garbage collection
        const auto items_after_advance = QGraphicsScene::items();

        for(QGraphicsItem* i: items_before_advance) {
            auto as = qgraphicsitem_cast<Asteroid*>(i);
            if (as && as->removeAble()) {
                removeItem(as);
                if (as->deleteAble()) delete as;
            }

            if( !items_after_advance.contains(i) )
                delete i;
        }
    }

    render(&painter);
    transmitter.sendFrame(frame);
}
