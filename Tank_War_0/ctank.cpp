#include "ctank.h"
CTank::CTank(QWidget *parent,int color_)
    : QLabel(parent),v(10)
{
    //初始化坦克的角度，坐标，速度
    angle=0;
    x=rand()%(parent->width());
    y=rand()%(parent->height());
    //初始化坦克按钮按下的情况
    for(int i=0;i<4;i++){
        keyPressedCondition[i]=false;
    }
    //加载性感坦克图
    color=color_;
    image=new QImage;
    if(color_==GREEN){
       image->load("D:/mypkudays/Tank_War/Tank_War_0/images/greentank.png");
    }else if(color_==RED){
        image->load("D:/mypkudays/Tank_War/Tank_War_0/images/redtank.png");
    }

}
QImage* CTank::getImage(){
    return image;
}
int CTank::getx(){
    return x;
}
int CTank::gety(){
    return y;
}
int CTank::getangle(){
    return angle;
}
bool* CTank::getKeyPressed(){
    return keyPressedCondition;
}
CTank::~CTank(){
    delete image;
}
void CTank::changeKeyPressed(bool *newcondition){
    for(int i=0;i<4;i++){
        keyPressedCondition[i]=newcondition[i];
    }
}
void CTank::changePosition(){
    //调用这个函数，根据键盘按钮的情况更新坦克的方向和位置
    if(keyPressedCondition[RIGHT])
        angle+=8;
    if(keyPressedCondition[LEFT])
        angle-=8;
    if(keyPressedCondition[UP]){
        y+=v*sin((double)angle/180*pi);
        x+=v*cos((double)angle/180*pi);
    }
    if(keyPressedCondition[DOWN]){
        y-=v*sin((double)angle/180*pi);
        x-=v*cos((double)angle/180*pi);
    }
    angle=angle%360;
    if(angle<0)angle=360+angle;
}
