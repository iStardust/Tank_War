#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include "cbullet.h"
#include "ctank.h"
#include "cwall.h"
#include <QKeyEvent>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QTransform>
#include <QWidget>
#include <deque>
#include <queue>
namespace Ui {
class Battlefield;
}

const int ONGOING = -1;
const int TIE = 0;
const int GREENWIN = 1;
const int REDWIN = 2;

class Battlefield : public QWidget {
  Q_OBJECT

public:
  explicit Battlefield(QWidget *parent = nullptr);
  ~Battlefield();

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *) override;

private:
  Ui::Battlefield *ui;
  CTank *myTank[2]; // 存放红坦克、绿坦克的指针
  std::deque<std::pair<CBullet *, QTimer *>>
      myBullets; // 存放所有的子弹和其对应的析构时钟
  CWall *walls;  // 存放墙

  // 时钟
  QTimer *timerForTank;
  QTimer *timerForBullet;
  QTimer *timerForChecking;

  void gameStart();
  int checkGame();
signals:
  // 坦克的移动与停止移动
  void tankKeyPressed();
  void tankKeyReleased();
  // 子弹的发射与所有子弹都消失
  void bulletKeyPressed();
  void allBulletDestroyed();
  void sendmessage();

private slots:
  // 更新坦克的位置
  void tankTimeout();
  // 更新子弹的位置
  void bulletTimeout();
  // 删除一个最早出现的子弹
  void delBullet();
  // 检查游戏情况
  void gameCheck();
  void on_buttonRestart_clicked();
  void on_buttonExit_clicked();
};

#endif // BATTLEFIELD_H
