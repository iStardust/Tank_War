#include "cbullet.h"

CBullet::CBullet(QWidget *parent,CTank *tank)
    : QLabel(parent),v(BULLETVELOCITY)
{
    color=tank->getcolor();
    angle=tank->getangle();
    x=tank->getBulletPos().x()-5;
    y=tank->getBulletPos().y()-5;
    image=new QImage;
    image->load("D:/mypkudays/Tank_War/Tank_War_0/images/bullet.png");
}

int CBullet::getcolor(){
    return color;
}
double CBullet::getx(){
    return x;
}
double CBullet::gety(){
    return y;
}
QImage* CBullet::getimage(){
    return image;
}
void CBullet::changePosition(){
    y+=v*sin(angle/180*pi);
    x+=v*cos(angle/180*pi);
}
void CBullet::rebound(){

}
