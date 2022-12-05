#include "tower.h"
#include <QPainter>
#include <QMovie>


static const qreal TOWER_SIZE=90;//塔防矩形的边长

MoonTower::MoonTower(qreal x, qreal y,GameController& c)
    :controller(c)
{
    //item是gif形式
    movie = new QMovie(QString::fromStdString(":/gif/tower3.gif"));
    movie->start();
    setPos(x, y);
    setData(GD_Type, GO_Tower);//为该图形元素添加额外的数据信息，类似于散列一样的键值对的形式
    time1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
    time2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    sumBlood=100;
    tmpBlood=100;
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
        //painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
       // painter->drawPath(shape());
    }
}


void MoonTower::advance(int phase)
{
    if(!phase) return; //第0阶段
    handleCollisions();
    //move();
}

void MoonTower::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions)
    {      
        if(collidingItem->data(GD_Type) == GO_Bullet)//1号子弹，表示被击中
        {
           tmpBlood-=2;
           if(tmpBlood<=0)
           {
               controller.deleteTower(this);
               return;
           }

        }
    }
}


QRectF GunTowerOne::boundingRect() const
{
    return QRectF(-TOWER_SIZE/4, -TOWER_SIZE/2,  TOWER_SIZE/2, TOWER_SIZE);
}

void GunTowerOne::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
     painter->drawPath(shape());
}

QPainterPath GunTowerOne::shape() const
{
    QPainterPath p;
    p.addEllipse(tmp, TOWER_SIZE, TOWER_SIZE);
    return p;
}

//void GunTowerOne::handleCollisions()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();
//    foreach (QGraphicsItem *collidingItem, collisions)
//    {
//        if (collidingItem->data(GD_Type) == GO_Monster) //撞到了怪兽，发射2号子弹,由怪兽控制
//        {
////            long long tmp=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
////            //cout<<tmp-time1<<","<<tmp-time2<<endl;
////            if(tmp-time1>1000)
////            {
////                controller.Shoot(this,collidingItem);
////                time1=tmp;
////               // cout<< "here"<<endl;
////            }
////            else if(tmp-time2>1000)
////            {
////                controller.Shoot(this,collidingItem);
////                time2=tmp;
////            }

//        }
//        if(collidingItem->data(GD_Type) == GO_Bullet)//1号子弹，表示被击中
//        {
//            //血量减少
//            tmpBlood-=2;
//            if(tmpBlood<=0)
//            {
//                controller.deleteTower(this);
//                return;
//            }

//        }
//    }

//}


//void GunTowerOne::advance(int phase)
//{
//    if(!phase) return; //第0阶段
//    handleCollisions();
//    //move();
//}
void GunTowerTwo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
     painter->drawPath(shape());
}

QPainterPath GunTowerTwo::shape() const
{
    QPainterPath p;
    p.addEllipse(tmp, TOWER_SIZE*1.5, TOWER_SIZE*1.5);
    return p;
}

//void GunTowerTwo::handleCollisions()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();
//    foreach (QGraphicsItem *collidingItem, collisions)
//    {
//        if (collidingItem->data(GD_Type) == GO_Monster) //撞到了怪兽，发射2号子弹
//        {
////            long long tmp=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
////            //cout<<tmp-time1<<","<<tmp-time2<<endl;
////            if(tmp-time1>1000)
////            {
////                controller.Shoot(this,collidingItem);
////                time1=tmp;
////               // cout<< "here"<<endl;
////            }
////            else if(tmp-time2>1000)
////            {
////                controller.Shoot(this,collidingItem);
////                time2=tmp;
////            }

//        }
//        if(collidingItem->data(GD_Type) == GO_Bullet)//1号子弹，表示被击中
//        {
//            tmpBlood-=2;
//            if(tmpBlood<=0)
//            {
//                controller.deleteTower(this);
//                return;
//            }
//        }
//    }

//}


//void GunTowerTwo::advance(int phase)
//{
//    if(!phase) return; //第0阶段
//    handleCollisions();
//    //move();
//}
void GunTowerThree::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
     painter->drawPath(shape());
}

QPainterPath GunTowerThree::shape() const
{
    QPainterPath p;
    p.addEllipse(tmp, TOWER_SIZE*1.5, TOWER_SIZE*1.5);
    return p;
}

//void GunTowerThree::handleCollisions()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();
//    foreach (QGraphicsItem *collidingItem, collisions)
//    {
//        if (collidingItem->data(GD_Type) == GO_Monster) //撞到了怪兽，发射2号子弹
//        {
////            long long tmp=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
////           // cout<<tmp-time1<<","<<tmp-time2<<endl;
////            if(tmp-time1>1000)
////            {
////                controller.Shoot(this,collidingItem);
////                time1=tmp;
////               // cout<< "here"<<endl;
////            }
////            else if(tmp-time2>1000)
////            {
////                controller.Shoot(this,collidingItem);
////                time2=tmp;
////            }

//        }
//        if(collidingItem->data(GD_Type) == GO_Bullet)//1号子弹，表示被击中
//        {
//            tmpBlood-=2;
//            if(tmpBlood<=0)
//            {
//                controller.deleteTower(this);
//                return;
//            }
//        }
//    }

//}


//void GunTowerThree::advance(int phase)
//{
//    if(!phase) return; //第0阶段
//    handleCollisions();
//    //move();
//}
void GunTowerFour::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
     painter->drawImage(boundingRect(), QImage(path));
     painter->drawPath(shape());
}

QPainterPath GunTowerFour::shape() const
{
    QPainterPath p;
    p.addEllipse(tmp, TOWER_SIZE*2, TOWER_SIZE*2);
    return p;
}

//void GunTowerFour::handleCollisions()
//{
//    QList<QGraphicsItem *> collisions = collidingItems();
//    foreach (QGraphicsItem *collidingItem, collisions)
//    {
//        if (collidingItem->data(GD_Type) == GO_Monster) //撞到了怪兽，发射2号子弹
//        {/*
//            long long tmp=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
//           // cout<<tmp-time1<<","<<tmp-time2<<endl;
//            if(tmp-time1>1000)
//            {
//                controller.Shoot(this,collidingItem);
//                time1=tmp;
//               // cout<< "here"<<endl;
//            }
//            else if(tmp-time2>1000)
//            {
//                controller.Shoot(this,collidingItem);
//                time2=tmp;
//            }*/

//        }
//        if(collidingItem->data(GD_Type) == GO_Bullet)//1号子弹，表示被击中
//        {
//            tmpBlood-=2;
//            if(tmpBlood<=0)
//            {
//                controller.deleteTower(this);
//                return;
//            }

//        }
//    }

//}


//void GunTowerFour::advance(int phase)
//{
//    if(!phase) return; //第0阶段
//    handleCollisions();
//    //move();
//}
