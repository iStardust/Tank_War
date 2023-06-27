#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <QWidget>
#include "ctank.h"
#include "cwall.h"
#include <QKeyEvent>
#include <QTimer>
#include <QTransform>
#include <QPainter>
#include <QPainterPath>
namespace Ui {
class Battlefield;
}

class Battlefield : public QWidget
{
    Q_OBJECT

public:
    explicit Battlefield(QWidget *parent = nullptr);
    ~Battlefield();
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent*) override;
private:
    Ui::Battlefield *ui;
    CTank* myTank[2];//存放红坦克、绿坦克的指针
    CWall* walls;//存放墙
    QTimer* timer;//时钟指针
    void gameStart();
signals:
    void keyPressed();
    void keyReleased();
private slots:
    void onTimeout();//每个30毫秒更新一次
};

#endif // BATTLEFIELD_H
