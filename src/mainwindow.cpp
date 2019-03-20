#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bar.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(this) {
  ui->setupUi(this);
  ui->graphicsView->setScene(&scene);
  ui->graphicsView->scale(10, 10);
  auto bar = new Bar(Qt::red, 1);
  bar->setPos(0, 0);
  scene.addItem(bar);
}

MainWindow::~MainWindow() { delete ui; }
