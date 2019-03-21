#include "matrixscene.h"

#include "bar.h"

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(32, 26, QImage::Format_RGB888),
      painter(&frame),
      player1HPBar(Qt::red, 1),
      player2HPBar(Qt::green, 1),
      player1PWBar(Qt::yellow, 0),
      player2PWBar(Qt::yellow, 0)
    {
    // set BG
    setBackgroundBrush(Qt::black);

    // setSize
    setSceneRect(0, 0, 32, 26);

    // init Frame
    out.pixels = Array2D<Color>(32, 26);
    frame.fill(Qt::black);
    for (int x = 0; x < out.pixels.getWidth(); x++) {
        for (int y = 0; y < out.pixels.getHeight(); y++) {
          out.pixels(x, y) = Color(0, 0, 0);
        }
    }
    transmitter.sendFrame(out);

    connect(this, &QGraphicsScene::changed, this, &MatrixScene::updateFrame);

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
    connect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
    timer.start(1000 / 33);

    // init Map
    // set pos
    player1HPBar.setPos(1, 0);
    player2HPBar.setPos(30, 0);
    player1PWBar.setPos(0, 0);
    player2PWBar.setPos(31, 0);

    // add bars
    addItem(&player1HPBar);
    addItem(&player2HPBar);
    addItem(&player1PWBar);
    addItem(&player2PWBar);

    upperPlayer = new Player(true, new QGamepad(1, this), &player2HPBar, &player2PWBar);
    lowerPlayer = new Player(false, new QGamepad(0, this), &player1HPBar, &player1PWBar);
    addItem(upperPlayer);
    addItem(lowerPlayer);

    // test items here
    auto ast = new Asteroid();
    ast->setPos(0, 10);
    addItem(ast);

    auto pow1 = new PowerUp();
    pow1->setPos(10, 10);
    addItem(pow1);
}

void MatrixScene::updateFrame() {
  render(&painter);
  for (int x = 0; x < out.pixels.getWidth(); x++) {
    for (int y = 0; y < out.pixels.getHeight(); y++) {
      auto pixel = frame.pixelColor(x, y);
      out.pixels(x, y) = Color(pixel.red(), pixel.green(), pixel.blue());
    }
  }
  transmitter.sendFrame(out);
}

void MatrixScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Left:
        lowerPlayer->moveBy(-1, 0);
        break;
    case Qt::Key_Right:
        lowerPlayer->moveBy(1, 0);
        break;
    case Qt::Key_Control:
        addItem(new Missile(lowerPlayer->pos() + QPointF(1, 0), Qt::red, lowerPlayer, false));
        break;
    case Qt::Key_Space:
        addItem(new Missile(upperPlayer->pos() + QPointF(1, 0), Qt::magenta, upperPlayer, true));
        break;
    default:
        break;
    }
}
