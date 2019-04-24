#include "matrixscene.h"

#include <QDir>
#include <QRandomGenerator>

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(32, 26, QImage::Format_RGB888),
      painter(&frame),
      player1HPBar(Qt::green, 1),
      player2HPBar(Qt::red, 1),
      player1PWBar(Qt::yellow, 0),
      player2PWBar(Qt::yellow, 0),
      lowerPlayer(false, 0, &player1HPBar, &player1PWBar,
                  this),
      upperPlayer(true, 1, &player2HPBar, &player2PWBar,
                  this),
      lowerBorder(false),
      upperBorder(true),
      counter_to_shrink(0) {
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

  // add players
  addItem(&upperPlayer);
  addItem(&lowerPlayer);

  // add borders
  addItem(&lowerBorder);
  addItem(&upperBorder);
}

sf::SoundBuffer *MatrixScene::getSoundBuffer(QString name) {
  if (buffers.empty()) {
    // load sound files
    QDir dir("data/sounds");
    QListIterator<QFileInfo> it(
        dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot));
    while (it.hasNext()) {
      QFileInfo file = it.next();
      sf::SoundBuffer *buffer = new sf::SoundBuffer;
      buffer->loadFromFile(file.filePath().toStdString());
      buffers[file.baseName()] = buffer;
    }
  }
  return buffers[name];
}

void MatrixScene::endGame(bool upper) {
  gameOver = true;
  lowerPlayer.gameOver();
  upperPlayer.gameOver();
  addRect(0, 0, 32, 26, Qt::NoPen, (upper) ? Qt::green : Qt::red);
  auto text = addText((upper) ? "P1" : "P2", QFont("Times", 10, QFont::Bold));
  text->setPos(5, -5);
  auto won = addText("WON!", QFont("Times", 9, QFont::Bold));
  won->setPos(-4, 8);
}

void MatrixScene::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      lowerPlayer.move(-1);
      break;
    case Qt::Key_Right:
      lowerPlayer.move(1);
      break;
    case Qt::Key_A:
      upperPlayer.move(-1);
      break;
    case Qt::Key_D:
      upperPlayer.move(1);
      break;
    case Qt::Key_Control:
      lowerPlayer.fire(true);
      break;
    case Qt::Key_Space:
      upperPlayer.fire(true);
      break;
    default:
      break;
  }
}

// main event loop
// advance_and_gc()
void MatrixScene::timerEvent(QTimerEvent *) {
  if (!gameOver) {
    // Spawn new asteroide
    if (QRandomGenerator::system()->bounded(config::chance::spawn_asteroide) ==
        0) {
      QVector<QPointF> players;
      players.append(upperPlayer.pos());
      players.append(lowerPlayer.pos());
      new Asteroid(this);
    }
    // Spawn new powerup
    if (QRandomGenerator::system()->bounded(config::chance::spawn_powerup) == 0)
      new PowerUp(this);

    // Move players closer
    counter_to_shrink++;
    if (counter_to_shrink == config::gameSpeed::time_between_shrink) {
      if (upperPlayer.pos().y() < (frame.height() - 6) / 2) {
        upperPlayer.moveBy(0, 2);
        upperBorder.moveBy(0, 2);
        lowerPlayer.moveBy(0, -2);
        lowerBorder.moveBy(0, -2);
      }
      counter_to_shrink = 0;
    }

    // Advance
    const auto items_before_advance = QGraphicsScene::items();

    // The basic 'advance' function  TODO call QGraphicsScene::advance()
    // instead???
    for (int i = 0; i < 2; ++i) {
      const auto items_ = items();

      upperPlayer.advance(i);  // alternative soultion; players do lookAround
                               // in phase 1, others in two
      lowerPlayer.advance(i);

      for (QGraphicsItem *item : items_) {
        if (item == &upperPlayer || item == &lowerPlayer) continue;
        item->advance(i);
      }
    }

    // Garbage collection
    const auto items_after_advance = QGraphicsScene::items();

    for (QGraphicsItem *i : items_before_advance) {
      auto as = qgraphicsitem_cast<Asteroid *>(i);
      if (as && as->removeAble()) {
        removeItem(as);
        if (as->deleteAble()) delete as;
      }

      if (!items_after_advance.contains(i)) delete i;
    }
  }

  render(&painter);
  transmitter.sendFrame(frame);
}


QPointF MatrixScene::getRandomEdgePoint(){
    using config::mapWidth;
    using config::mapHeight;

    QPointF ret;

    qreal l1 = QRandomGenerator::global()->bounded(static_cast<quint32>((mapWidth + mapHeight)/2));

    if(l1 > (mapWidth/2.0)){
        ret.setX(mapWidth/2.0);
        ret.setY(l1 - (mapWidth/2.0));
    }
    else{
        ret.setX(l1);
        ret.setY(mapHeight/2.0);
    }

    if(QRandomGenerator::global()->bounded(0, 2) == 1)
        ret.ry()*=-1;

    if(QRandomGenerator::global()->bounded(0, 2) == 1)
        ret.rx()*=-1;

    ret+=QPointF{config::mapWidth/2.0, config::mapHeight/2.0};

    qDebug() << ret;

    return ret;
}
