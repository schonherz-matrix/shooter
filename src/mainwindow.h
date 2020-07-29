#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "matrixscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  static int const EXIT_CODE_REBOOT;

  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void reboot();

 private:
  Ui::MainWindow *ui;
  MatrixScene scene;
};

#endif  // MAINWINDOW_H
