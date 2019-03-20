#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <common/frame.h>
#include <muebtransmitter.h>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QPainter>

#include "player.h"
#include "asteroid.h"

class MatrixScene : public QGraphicsScene {
  Q_OBJECT

 public:
  MatrixScene(QObject *parent = nullptr);

 public slots:
  void updateFrame();

 private:
  Frame out;
  QImage frame;
  QPainter painter;
  MUEBTransmitter transmitter;

  Player* upperPlayer;
  Player* lowerPlayer;
};

#endif  // MATRIXSCENE_H
