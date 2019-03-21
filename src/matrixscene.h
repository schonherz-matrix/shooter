#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <common/frame.h>
#include <muebtransmitter.h>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QGamepadManager>
#include "bar.h"
#include "player.h"
#include "asteroid.h"
#include "powerup.h"
#include "missile.h"

class MatrixScene : public QGraphicsScene {
  Q_OBJECT

 public:
  MatrixScene(QObject *parent = nullptr);

 public slots:
  void updateFrame();
  void advance();

 private:
  Frame out;
  QImage frame;
  QPainter painter;
  MUEBTransmitter transmitter;
  QTimer timer;

  QList<Player*> players;
  QList<Asteroid*> asteroids;
  QList<PowerUp*> powerups;
  QList<Missile*> missiles;

  Bar player1HPBar;
  Bar player2HPBar;
  Bar player1PWBar;
  Bar player2PWBar;

  Player* upperPlayer;
  Player* lowerPlayer;

  // QGraphicsScene interface
protected:
  void keyPressEvent(QKeyEvent *event) override;
};

#endif  // MATRIXSCENE_H
