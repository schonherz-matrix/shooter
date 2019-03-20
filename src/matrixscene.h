#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <common/frame.h>
#include <muebtransmitter.h>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QTimer>

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
  QTimer timer;
};

#endif  // MATRIXSCENE_H
