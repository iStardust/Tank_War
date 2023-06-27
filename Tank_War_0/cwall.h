#ifndef CWALL_H
#define CWALL_H

#include <QObject>
#include <QLabel>
#include <QPolygon>
#include <QLine>
#include <vector>
#include "ctank.h"

class CWall : public QLabel
{
    Q_OBJECT
public:
    explicit CWall(QWidget *parent = nullptr);
    //判断坦克是否撞墙
    bool tankCrashOnWall(CTank* tank);
    //返回墙
    const std::vector<QPolygon>& getWalls();
private:
    //所有的墙壁
    std::vector<QPolygon> walls;

signals:

};

#endif // CWALL_H
