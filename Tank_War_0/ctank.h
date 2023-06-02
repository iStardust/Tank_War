#ifndef CTANK_H
#define CTANK_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <cmath>
#include <stdlib.h>
#include <time.h>
const int RED=1;
const int GREEN=0;
const int RIGHT=0;
const int UP=1;
const int DOWN=2;
const int LEFT=3;
class CTank : public QLabel
{
    Q_OBJECT
public:
    explicit CTank(QWidget *parent = nullptr,int color_=GREEN);
    ~CTank();
    //改变按钮被按下的情况
    void changeKeyPressed(bool *newcondition);
    //改变坦克的位置
    void changePosition();
    //获取坦克的坐标,旋转角度,按钮按下情况
    int getx();
    int gety();
    int getangle();
    bool* getKeyPressed();
    //获取图片
    QImage* getImage();
private:
    int angle;//角度
    //上下左右按钮是否按下
    bool keyPressedCondition[4];
    //坦克的坐标、速度、颜色等参数
    int x;
    int y;
    const int v;
    const double pi = acos(-1);
    int color;
    //坦克图片
    QImage* image;


signals:
private slots:

};

#endif // CTANK_H
