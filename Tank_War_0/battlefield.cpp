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
    myTank[GREEN]->setPixmap(QPixmap::fromImage(*myTank[GREEN]->getImage()));
    myTank[RED]->setPixmap(QPixmap::fromImage(*myTank[RED]->getImage()));
    myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
    myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
    myTank[GREEN]->show();
    myTank[RED]->show();
    //时钟在按钮按下后每隔30毫秒发出timeout()信号，从而调用槽函数onTimeout()
    timer=new QTimer(this);
    timer->setInterval(30);
    connect(timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    connect(this, SIGNAL(keyPressed()), timer, SLOT(start()));
    connect(this, SIGNAL(keyReleased()), timer, SLOT(stop()));

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
    emit keyReleased();
}


void Battlefield::onTimeout(){
    //改变坦克位置,旋转角度,并重新显示坦克
    myTank[GREEN]->changePosition();
    myTank[RED]->changePosition();
    myTank[GREEN]->setPixmap(
        QPixmap::fromImage(*myTank[GREEN]->getImage()).transformed(QTransform().rotate(myTank[GREEN]->getangle())));
    myTank[RED]->setPixmap(
        QPixmap::fromImage(*myTank[RED]->getImage()).transformed(QTransform().rotate(myTank[RED]->getangle())));
    myTank[GREEN]->setGeometry(myTank[GREEN]->getx(),myTank[GREEN]->gety(),60,60);
    myTank[RED]->setGeometry(myTank[RED]->getx(),myTank[RED]->gety(),60,60);
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

