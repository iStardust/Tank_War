#include "battlefield.h"
#include "ui_battlefield.h"

Battlefield::Battlefield(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Battlefield)
{
    ui->setupUi(this);
    //加载红绿坦克
    srand((unsigned)time(NULL));
    myTank[GREEN]=new CTank(this,GREEN);
    myTank[RED]=new CTank(this,RED);
    myTank[GREEN]->setPixmap(
        QPixmap::fromImage(*myTank[GREEN]->getImage()).transformed(QTransform().rotate(myTank[GREEN]->getangle())));
    myTank[RED]->setPixmap(
        QPixmap::fromImage(*myTank[RED]->getImage()).transformed(QTransform().rotate(myTank[RED]->getangle())));
    myTank[GREEN]->setAlignment(Qt::AlignCenter);
    myTank[RED]->setAlignment(Qt::AlignCenter);
    myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
    myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
    myTank[GREEN]->show();
    myTank[RED]->show();
    //时钟在按钮按下后每隔30毫秒发出timeout()信号，从而调用槽函数onTimeout()
    timer=new QTimer(this);
    timer->setInterval(15);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    //检测到键盘有按下就启动计时器
    connect(this, SIGNAL(keyPressed()), timer, SLOT(start()));
    //检测到keyReleased()信号就停止计时器
    //注意：在keyReleaseEvent()中只有当所有按钮都释放才会发射keyReleased信号
    //也就是说，这样能够实现长按按钮情况下坦克的连续移动、转弯等操作
    connect(this, SIGNAL(keyReleased()), timer, SLOT(stop()));
    walls=new CWall(this);


}

void Battlefield::keyPressEvent(QKeyEvent *event)
{
    //获得之前的按钮情况
    bool* newred=new bool[4];
    bool* newgreen=new bool[4];
    bool* oldred=myTank[RED]->getKeyPressed();
    bool* oldgreen=myTank[GREEN]->getKeyPressed();
    for(int i=0;i<4;i++){
        newred[i]=oldred[i];
        newgreen[i]=oldgreen[i];
    }
    if (event->isAutoRepeat()) {
        event->ignore();
    } else {
        switch(event->key()){
        case Qt::Key_Right:
            newgreen[RIGHT]=true;
            break;
        case Qt::Key_Up:
            newgreen[UP]=true;
            break;
        case Qt::Key_Left:
            newgreen[LEFT]=true;
            break;
        case Qt::Key_Down:
            newgreen[DOWN]=true;
            break;
        case Qt::Key_W:
            newred[UP]=true;
            break;
        case Qt::Key_A:
            newred[LEFT]=true;
            break;
        case Qt::Key_S:
            newred[DOWN]=true;
            break;
        case Qt::Key_D:
            newred[RIGHT]=true;
            break;
        default:
            break;
        }
        myTank[GREEN]->changeKeyPressed(newgreen);
        myTank[RED]->changeKeyPressed(newred);
    }
    emit keyPressed();
}
void Battlefield::keyReleaseEvent(QKeyEvent *event)
{
    //获得之前的按钮情况
    bool* newred=new bool[4];
    bool* newgreen=new bool[4];
    bool* oldred=myTank[RED]->getKeyPressed();
    bool* oldgreen=myTank[GREEN]->getKeyPressed();
    for(int i=0;i<4;i++){
        newred[i]=oldred[i];
        newgreen[i]=oldgreen[i];
    }
    if (event->isAutoRepeat()) {
        event->ignore();
    } else {
        switch(event->key()){
        case Qt::Key_Right:
            newgreen[RIGHT]=false;
            break;
        case Qt::Key_Up:
            newgreen[UP]=false;
            break;
        case Qt::Key_Left:
            newgreen[LEFT]=false;
            break;
        case Qt::Key_Down:
            newgreen[DOWN]=false;
            break;
        case Qt::Key_W:
            newred[UP]=false;
            break;
        case Qt::Key_A:
            newred[LEFT]=false;
            break;
        case Qt::Key_S:
            newred[DOWN]=false;
            break;
        case Qt::Key_D:
            newred[RIGHT]=false;
            break;
        default:
            break;
        }
        myTank[GREEN]->changeKeyPressed(newgreen);
        myTank[RED]->changeKeyPressed(newred);
    }
    //如果所有的按钮都释放了，就发射keyReleased()信号，从而结束计时器
    bool allReleased=true;
    for(int i=0;i<4;i++){
        if(newred[i]){
            allReleased=false;
            break;
        }
        if(newgreen[i]){
            allReleased=false;
            break;
        }
    }
    if(allReleased){
        emit keyReleased();
    }
}

void Battlefield::paintEvent(QPaintEvent*){
    //draw walls filled with darkGray color
    QPainter painter(this);
    painter.setPen(Qt::black);
    QPainterPath mypath;
    QBrush mybrush(Qt::darkGray);
    for(auto polygon:(walls->getWalls())){
        mypath.clear();
        mypath.addPolygon(polygon);
        painter.fillPath(mypath,mybrush);
        //painter.drawPolygon(polygonf);
    }
}

void Battlefield::onTimeout(){
    //改变坦克位置,旋转角度,并重新显示坦克
    //if crash after changing postion, go back to the old position
    double oldx,oldy; int oldangle;
    int tmpcolor[2]={GREEN,RED};
    for(auto color:tmpcolor){
        oldx=myTank[color]->getx();
        oldy=myTank[color]->gety();
        oldangle=myTank[color]->getangle();
        myTank[color]->changePosition();
        if(walls->tankCrashOnWall(myTank[color])){
            myTank[color]->changePosition(oldx,oldy,oldangle);
        }
    }
    myTank[GREEN]->setPixmap(
        QPixmap::fromImage(*myTank[GREEN]->getImage()).transformed(QTransform().rotate(myTank[GREEN]->getangle())));
    myTank[RED]->setPixmap(
        QPixmap::fromImage(*myTank[RED]->getImage()).transformed(QTransform().rotate(myTank[RED]->getangle())));
    myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
    myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
    //以下代码用于debug,查看坦克矩形的坐标是否显示正确
    ui->testlabel->setText(myTank[RED]->getRect());
}
void Battlefield::mousePressEvent(QMouseEvent *event){
    ui->mouse->setText("("+QString::number(event->x())+","+QString::number(event->y())+")"
                       +"leftup:("+QString::number(myTank[RED]->getx())+","+QString::number(myTank[RED]->gety())+")");
}

Battlefield::~Battlefield()
{
    delete ui;
    delete myTank[0];
    delete myTank[1];
    delete timer;
}
void gameStart(){

}

