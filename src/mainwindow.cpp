#include "mainwindow.h"

#include "ui_mainwindow.h"

int const MainWindow::EXIT_CODE_REBOOT = -123456789;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), scene(this) {
  ui->setupUi(this);
  ui->graphicsView->setScene(&scene);
  ui->graphicsView->scale(10, 10);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::reboot() { qApp->exit(MainWindow::EXIT_CODE_REBOOT); }
