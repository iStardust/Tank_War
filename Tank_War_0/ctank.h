#ifndef CTANK_H
#define CTANK_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QPoint>
#include <QString>
#include <cmath>
#include <stdlib.h>
#include <time.h>

const int RED=1;
const int GREEN=0;
const int RIGHT=0;
const int UP=1;
const int DOWN=2;
const int LEFT=3;
const double pi = acos(-1);
//坦克的速度
const double VELOCITY=2;



class myRect{
private:
    QPoint points[4];
public:
    myRect();
    //给出中心，长，宽，旋转角度
    myRect(QPoint&& center,int length,int width,int angle);
    //Copy constructor
    myRect(const myRect& r);
    ~myRect();
    //以中心、旋转角度、长、宽为参数更新矩形
    void updateRect(QPoint&& center,int length,int width,int angle);
//    //判断一个点是否在矩形内部
//    bool checkInside(QPoint& p);
//    //把坐标转换成QString,用于debug
    QString getPointstr();
    QPoint* getPoints();

};

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
    void changePosition(double x,double y,int angle);
    //获取坦克的坐标,旋转角度,按钮按下情况
    double getx();
    double gety();
    int getangle();
    bool* getKeyPressed();
    //获取图片
    QImage* getImage();
    //获取矩形信息，用于debug
    QString getRect();
    //获取四个坐标
    QPoint* getPoints();
private:
    int angle;//角度
    //上下左右按钮是否按下
    bool keyPressedCondition[4];
    //坦克的坐标、速度、颜色、所占据的矩形方框等参数
    double x;
    double y;
    const double v;
    int color;
    myRect tankRect;
    //QPoint[4];
    //坦克图片
    QImage* image;

signals:
private slots:

};

#endif // CTANK_H
