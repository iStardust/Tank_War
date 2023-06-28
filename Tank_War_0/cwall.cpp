#include "cwall.h"

CWall::CWall(QWidget *parent)
    : QLabel{parent}
{
    int x=parent->width();
    int y=parent->height();
    //先添加边框
    walls.push_back(QPolygon(QRect(QPoint(0,0),QPoint(x,10))));
    walls.push_back(QPolygon(QRect(QPoint(0,0),QPoint(10,y))));
    walls.push_back(QPolygon(QRect(QPoint(x-10,0),QPoint(x,y))));
    walls.push_back(QPolygon(QRect(QPoint(0,y-10),QPoint(x,y))));
    //再随机生成墙壁
    int num=15;
    while(num--){
        int px=rand()%x;
        int py=rand()%y;
        int l=rand()%(x/5)+(x/10);
        int m=num%4;
        //生成横竖撇捺的墙
        if(m==0){
            walls.push_back(QPolygon(QRect(QPoint(px-l/2,py-5),QPoint(px+l/2,py+5))));
        }
        if(m==1){
            walls.push_back(QPolygon(QRect(QPoint(px-5,py-l/2),QPoint(px+5,py+l/2))));
        }
        if(m==2){
            QPolygon w;
            w<<QPoint(px-l/2,py-l/2)<<QPoint(px+l/2,py+l/2)
              <<QPoint(px+l/2-15,py+l/2)<<QPoint(px-l/2-15,py-l/2);
            walls.push_back(w);
        }
        if(m==3){
            QPolygon w;
            w<<QPoint(px-l/2,py+l/2)<<QPoint(px+l/2,py-l/2)
              <<QPoint(px+l/2-15,py-l/2)<<QPoint(px-l/2-15,py+l/2);
            walls.push_back(w);

        }

    }
}
CWall::~CWall(){
    walls.clear();
}

const std::vector<QPolygon>& CWall::getWalls(){
    return walls;
}

bool CWall::tankCrashOnWall(CTank* tank){
    //传入坦克 判断坦克是否撞墙
    QPolygon tankPolygon;
    QPoint* points=tank->getPoints();
    for(int i=0;i<4;i++){
        tankPolygon<<points[i];
    }
    for(auto it:walls){
        if(it.intersects(tankPolygon)){
            return true;
        }
    }
    return false;
}
