#include "matrixscene.h"
#include "player.h"

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

  Player* upperPlayer = new Player(true);
  Player* lowerPlayer = new Player(false);

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
