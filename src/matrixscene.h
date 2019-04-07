#ifndef MATRIXSCENE_H
#define MATRIXSCENE_H

#include <muebtransmitter.h>
#include <QGraphicsScene>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QTimer>
#include <QList>
#include <QGamepadManager>
#include "bar.h"
#include "asteroid.h"
#include "powerup.h"
#include "missile.h"
#include "config.h"
#include <SFML/Audio.hpp>
#include "player.h"
#include "border.h"

class MatrixScene : public QGraphicsScene {
  Q_OBJECT

 public:
  MatrixScene(QObject *parent = nullptr);
  sf::SoundBuffer* getSoundBuffer(QString name);

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

  Player* upperPlayer;
  Player* lowerPlayer;
  Border lowerBorder;
  Border upperBorder;

  config::tick counter_to_shrink;

  QMap<QString, sf::SoundBuffer*> buffers;
  bool gameOver = false;

  // QGraphicsScene interface
protected:
  void keyPressEvent(QKeyEvent *event) override;

  // QObject interface
protected:
  void timerEvent(QTimerEvent *event) override;
};

#endif  // MATRIXSCENE_H
