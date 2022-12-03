#include "bullet.h"
#include <QPainter>
#include <QMovie>
#include <QDebug>

static const qreal BULLET_SIZE=15;//子弹矩形的边长，合适待调整
static const int speed=10;


bullet::bullet(QPointF s, QPointF d,GameController& g)
    :controller(g)
{
    movie = new QMovie(QString::fromStdString(":/gif/bullet1.gif"));
    movie->start();

    src=s;
    dest=d;
    tmp=src;
    setPos(s.x(),s.y());
    setData(GD_Type, GO_Bullet);

}


QRectF bullet::boundingRect() const //override
{
    return QRectF(-BULLET_SIZE/2, -BULLET_SIZE/2,  BULLET_SIZE, BULLET_SIZE  );

}

void bullet::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());
        painter->drawRect(boundingRect());
    }
}


void bullet::advance(int step)//step参数为重载时系统给的
{
    if(!step) return;

    //更新monster
    if(move())//monster移动
    {
        controller.deleteBullet(this);
    }
    handleCollisions();

}


//注意子弹运动的路线是直线，超过屏幕后应当及时delete
bool bullet::move()//scene是910*560
{
    if(tmp.x()<0||tmp.x()>910||tmp.y()<0||tmp.y()>560)
    {   //cout <<"here"<<endl;
        return true;
}
    if(dest.x()==src.x())//竖线
    {
        if(src.y()<dest.y()) //向下
        {
            tmp.setY(tmp.y()+12);
        }

        else//向上
        {
            tmp.setY(tmp.y()-12);
        }

    }

    else if(dest.y()==src.y())//横线
    {
        if(src.x()<dest.x()) //向右
        {
            tmp.setX(tmp.x()+12);
        }

        else//向左
        {
            tmp.setX(tmp.x()-12);
        }
    }

    else//斜线
    {
        qreal k=(dest.y()-src.y())/(dest.x()-src.x());//斜率

        //cout<< k<<endl;

        if(k>0)
        {
            qreal preX=tmp.x();
            if(src.x()<dest.x()) //向右下
            {

                tmp.setX(tmp.x()+10);
                //根据直线斜率增加y
                tmp.setY(tmp.y()+(tmp.x()-preX)*k);
            }
            else if(src.x()>dest.x()) //向左上
            {
                tmp.setX(tmp.x()-10);
                //根据直线斜率增加y
                tmp.setY(tmp.y()-(preX-tmp.x())*k);
             }
        }
        else if(k<0)
        {
            k=-k;//绝对值，方便计算
            qreal preX=tmp.x();
            if(src.x()<dest.x()) //向右上
            {

                tmp.setX(tmp.x()+10);
                //根据直线斜率增加y
                tmp.setY(tmp.y()-(tmp.x()-preX)*k);
             }
            else if(src.x()>dest.x()) //向左下
            {
                //cout << "here"<<endl;
                tmp.setX(tmp.x()-10);
                //根据直线斜率增加y
                tmp.setY(tmp.y()+(preX-tmp.x())*k);
            }
        }
    }



    setPos(tmp.x(),tmp.y());//重新定位
    //qDebug()<<tmp;

    return false;
}

void bullet::handleCollisions()//1号子弹，怪兽打塔，所以遇到塔自己消失
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions)
    {
        if(collidingItem->data(GD_Type) == GO_GunTower)
        {
           controller.deleteBullet(this);
        }
    }
}
void bulletTwo::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());
        painter->drawRect(boundingRect());
    }
}

void bulletTwo::advance(int step)//step参数为重载时系统给的
{
    if(!step) return;

    //更新monster
    if(move())//monster移动
    {
        controller.deleteBullet(this);
    }

    handleCollisions();
}

void bulletTwo::handleCollisions()//2号子弹，塔打怪兽，所以遇到怪兽自己消失
{
    QList<QGraphicsItem *> collisions = collidingItems();
    foreach (QGraphicsItem *collidingItem, collisions)
    {
        if(collidingItem->data(GD_Type) == GO_Monster)
        {
           controller.deleteBullet(this);
        }
    }

}
