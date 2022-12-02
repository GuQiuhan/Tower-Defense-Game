#include "tower.h"
#include <QPainter>
#include <QMovie>

enum GameObjectsData {
    GD_Type
};

enum GameObjectTypes {
    GO_Tower,
    GO_Monster,
    GO_Bullet
};

static const qreal TOWER_SIZE=90;//塔防矩形的边长

MoonTower::MoonTower(qreal x, qreal y)
{
    //item是gif形式
    movie = new QMovie(QString::fromStdString(":/gif/tower3.gif"));
    movie->start();
    setPos(x, y);
    setData(GD_Type, GO_Tower);//为该图形元素添加额外的数据信息，类似于散列一样的键值对的形式
}

QRectF MoonTower::boundingRect() const
{
    //此处的参数适合，有待改进
    return QRectF(-TOWER_SIZE/2, -TOWER_SIZE,  TOWER_SIZE, TOWER_SIZE*1.5 );//以item中心为原点，矩形的范围实际是四倍于实际区域的：以元素坐标 (x, y) 为中心，边长为TOWER_SIZE * 2的正方形
}

void MoonTower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());
        painter->drawRect(boundingRect());//可以画出相应的item的Rect大小

    }
}

//QPainterPath MoonTower::shape() const //实际的形状
//{
//    QPainterPath p;
//    p.addEllipse(tmp, TOWER_SIZE, TOWER_SIZE/2);
//    return p;
//}


void MoonTower::advance(int phase)
{
    if(!phase) return; //第0阶段
    //move();
}

QRectF GunTowerOne::boundingRect() const
{
    return QRectF(-TOWER_SIZE/4, -TOWER_SIZE/2,  TOWER_SIZE/2, TOWER_SIZE);
}
void GunTowerOne::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
}

void GunTowerTwo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
}
void GunTowerThree::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
}
void GunTowerFour::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
}
