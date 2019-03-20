#include "matrixscene.h"
#include "bar.h"

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(32, 26, QImage::Format_RGB888),
      painter(&frame),
      player1HPBar(Qt::red, 1),
      player2HPBar(Qt::green, 1),
      player1PWBar(Qt::yellow, 0),
      player2PWBar(Qt::yellow, 0) {
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

  // init Timer
  connect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
  timer.start(1000 / 33);

  // init Map
  // set pos
  player1HPBar.setPos(0, 0);
  player2HPBar.setPos(31, 0);
  player1PWBar.setPos(1, 0);
  player2PWBar.setPos(30, 0);

  // add bars
  addItem(&player1HPBar);
  addItem(&player2HPBar);
  addItem(&player1PWBar);
  addItem(&player2PWBar);
  upperPlayer = new Player(true, &player1HPBar);
  lowerPlayer = new Player(false, &player2HPBar);

  addItem(upperPlayer);
  addItem(lowerPlayer);
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
