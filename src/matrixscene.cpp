#include "matrixscene.h"
#include "bar.h"

MatrixScene::MatrixScene(QObject *parent)
    : QGraphicsScene(parent),
      frame(32, 26, QImage::Format_RGB888),
      painter(&frame) {
  // set BG
  setBackgroundBrush(Qt::black);

  // setSize
  setSceneRect(0, 0, 32, 26);

  // initFrame
  out.pixels = Array2D<Color>(32, 26);
  frame.fill(Qt::black);
  for (int x = 0; x < out.pixels.getWidth(); x++) {
    for (int y = 0; y < out.pixels.getHeight(); y++) {
      out.pixels(x, y) = Color(0,0,0);
    }
  }
  transmitter.sendFrame(out);

  connect(this, &QGraphicsScene::changed, this, &MatrixScene::updateFrame);

  auto upperBarOnRight = new Bar(Qt::red, 1);
  auto lowerBarOnLeft = new Bar(Qt::red, 1);

  upperPlayer = new Player(true, upperBarOnRight);
  lowerPlayer = new Player(false, lowerBarOnLeft);

  addItem(upperPlayer);
  addItem(lowerPlayer);

  addItem(upperBarOnRight);
  addItem(lowerBarOnLeft);

  Asteroid *a1 = new Asteroid();
  Asteroid *a2 = new Asteroid();
  Asteroid *a3 = new Asteroid();
  Asteroid *a4 = new Asteroid();

  a1->setPos(2, 2);
  a2->setPos(10, 10);
  a3->setPos(16, 8);
  a4->setPos(20, 14);

  a2->hit();

  a3->hit();

  addItem(a1);
  addItem(a2);
  addItem(a3);
  addItem(a4);
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
