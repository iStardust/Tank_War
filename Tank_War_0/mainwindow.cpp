#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QImage>
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->startButton, &QPushButton::clicked, [=]() {
    mybattlefield = new Battlefield(this);
    mybattlefield->setWindowFlags(Qt::Window);
    mybattlefield->show();
  });

  QPixmap bgImg("://images/background.png");
  bgImg = bgImg.scaled(this->size(), Qt::IgnoreAspectRatio);
  QPalette palette;
  palette.setBrush(QPalette::Window, bgImg);
  this->setPalette(palette);
}

MainWindow::~MainWindow() {
  delete ui;
  delete mybattlefield;
}

void MainWindow::recievemessage(){
  delete mybattlefield;
  mybattlefield = new Battlefield(this);
  mybattlefield->setWindowFlags(Qt::Window);
  mybattlefield->show();
}
