#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <muebtransmitter.h>
#include <QGamepadManager>
#include <QGraphicsScene>
#include <QImage>
#include <QPainter>
#include <QTimer>
#include <SFML/Audio.hpp>
#include "asteroid.h"
#include "bar.h"
#include "border.h"
#include "config.h"
#include "missile.h"
#include "player.h"
#include "powerup.h"

class MatrixScene : public QGraphicsScene {
  Q_OBJECT

 public:
  MatrixScene(QObject* parent = nullptr);
  sf::SoundBuffer* getSoundBuffer(QString name);
  gainput::InputManager manager;
  QPointF getRandomEdgePoint();

 public slots:
  void endGame(bool upper);

 private:
  QImage frame;
  QPainter painter;
  MUEBTransmitter transmitter;
  int timerID;

  Bar player1HPBar;
  Bar player2HPBar;
  Bar player1PWBar;
  Bar player2PWBar;

  QMap<QString, sf::SoundBuffer*> buffers;

  Player lowerPlayer;
  Player upperPlayer;

  Border lowerBorder;
  Border upperBorder;

  config::tick counter_to_shrink;

  bool gameOver = false;

 protected:
  // QGraphicsScene interface
  void keyPressEvent(QKeyEvent* event) override;
  // QObject interface
  void timerEvent(QTimerEvent* event) override;
};

#endif  // MATRIXSCENE_H
