#include "monster.h"
#include <QMovie>
#include <iostream>
#include <QList>
#include <QDebug>
#include "gamecontroller.h"
using namespace std;




static const qreal MONSTER_SIZE=30;//怪兽矩阵的边长

Monster::Monster(vector<QPointF> p,GameController & c)//将controller也传过来，因为advance里需要传回给controller处理
    :controller(c)
{
    setPic();//创建时需要确定图片
    tmp_path=p;//路径
    tmp=p[0];//初始位置为路径开头
    index=0;
    movie = new QMovie(QString::fromStdString(Pic));
    movie->start();

    pause=false;
    sumBlood=10;
    tmpBlood=10;
    setData(GD_Type, GO_Monster);
    time1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
    time2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    time3=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
    time4=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

Monster::Monster(Monster& m)
    :controller(m.controller)
    ,pause(m.pause)
    ,tmp_path(m.tmp_path)
    ,tmp(m.tmp)
    ,index(m.index)
    ,Pic(m.Pic)
    ,movie(m.movie)
{

}


void Monster::setPic()
{
    Pic=":/gif/bat.gif";
}

Monster::~Monster()
{
    delete movie;
}

void Monster::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,MONSTER_SIZE*2,6);//绘制矩形
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        qreal rate = tmpBlood/sumBlood;//计算比例
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,rate*MONSTER_SIZE*2,6);//绘制矩形
    }




}

QRectF Monster::boundingRect() const
{
    return QRectF(-MONSTER_SIZE, -MONSTER_SIZE, MONSTER_SIZE*2, MONSTER_SIZE*2);//参数合适，有待调节

}


bool Monster::move()
{
    if(pause==true) return false;//停止运动
    if(tmp.x()==tmp_path[tmp_path.size()-1].x()&&tmp.y()==tmp_path[tmp_path.size()-1].y())//到达路径终点
    {
        return true;
    }

    else
    {
        if(tmp.x()==tmp_path[index+1].x()&&tmp.y()==tmp_path[index+1].y()) index++;//index应当不会越界

        if(tmp.x()==tmp_path[index+1].x())//竖线
        {
            if(tmp.y()<tmp_path[index+1].y()) //向下
            {
                tmp.setY(tmp.y()+1);
                if(tmp.y()>tmp_path[index+1].y())
                    tmp.setY(tmp_path[index+1].y());
            }

            else//向上
            {
                tmp.setY(tmp.y()-1);
                if(tmp.y()<tmp_path[index+1].y())
                    tmp.setY(tmp_path[index+1].y());
            }

        }

        else if(tmp.y()==tmp_path[index+1].y())//横线
        {
            if(tmp.x()<tmp_path[index+1].x()) //向右
            {
                tmp.setX(tmp.x()+1);
                if(tmp.x()>tmp_path[index+1].x())
                    tmp.setX(tmp_path[index+1].x());
            }

            else//向左
            {
                tmp.setX(tmp.x()-1);
                if(tmp.x()<tmp_path[index+1].x())
                    tmp.setX(tmp_path[index+1].x());
            }
        }

        else//斜线
        {
            qreal k=(tmp_path[index+1].y()-tmp.y())/(tmp_path[index+1].x()-tmp.x());//斜率

            //cout<< k<<endl;

            if(k>0)
            {
                qreal preX=tmp.x();
                if(tmp.x()<tmp_path[index+1].x()) //向右下
                {

                    tmp.setX(tmp.x()+0.4);
                    if(tmp.x()>tmp_path[index+1].x())
                        tmp.setX(tmp_path[index+1].x());
                    //根据直线斜率增加y
                    tmp.setY(tmp.y()+(tmp.x()-preX)*k);
                    if(tmp.y()>tmp_path[index+1].y())
                        tmp.setY(tmp_path[index+1].y());
                }
                else if(tmp.x()>tmp_path[index+1].x()) //向左上
                {
                    tmp.setX(tmp.x()-0.4);
                    if(tmp.x()<tmp_path[index+1].x())
                        tmp.setX(tmp_path[index+1].x());
                    //根据直线斜率增加y
                    tmp.setY(tmp.y()-(preX-tmp.x())*k);
                    if(tmp.y()<tmp_path[index+1].y())
                        tmp.setY(tmp_path[index+1].y());
                }
            }
            else if(k<0)
            {
                k=-k;//绝对值，方便计算
                qreal preX=tmp.x();
                if(tmp.x()<tmp_path[index+1].x()) //向右上
                {

                    tmp.setX(tmp.x()+0.4);
                    if(tmp.x()>tmp_path[index+1].x())
                        tmp.setX(tmp_path[index+1].x());
                    //根据直线斜率增加y
                    tmp.setY(tmp.y()-(tmp.x()-preX)*k);
                    if(tmp.y()<tmp_path[index+1].y())
                        tmp.setY(tmp_path[index+1].y());
                }
                else if(tmp.x()>tmp_path[index+1].x()) //向左下
                {
                    //cout << "here"<<endl;
                    tmp.setX(tmp.x()-0.4);
                    if(tmp.x()<tmp_path[index+1].x())
                        tmp.setX(tmp_path[index+1].x());
                    //根据直线斜率增加y
                    tmp.setY(tmp.y()+(preX-tmp.x())*k);

                    if(tmp.y()>tmp_path[index+1].y())
                        tmp.setY(tmp_path[index+1].y());
                }
            }
        }

        setPos(tmp.x(),tmp.y());//重新定位
    }


    return false;

}

void Monster::advance(int step)//step参数为重载时系统给的
{
    if(!step) return;

    //更新monster
    move();//monster移动
    handleCollisions();

}


void Monster::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();
    bool flag=true;
    foreach (QGraphicsItem *collidingItem, collisions)
    {
        //qDebug()<< collidingItem->data(GD_Type);
        if (collidingItem->data(GD_Type) == GO_Tower) //撞到了近战塔
        {
            setPause();
            flag=false;
        }
        if(collidingItem->data(GD_Type) == GO_GunTower)
        {
            //cout<<"here"<<endl;
            //使用时间判断，防止一直在打子弹
            long long tmp=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            if(tmp-time1>1000)
            {
                //cout<< "s"<<endl;
                controller.Shoot(this,collidingItem);
                time1=tmp;
            }
            else if(tmp-time2>1500)
            {
                controller.Shoot(this,collidingItem);
                time2=tmp;
            }
            if(tmp-time3>1000)
            {
                controller.Shoot(collidingItem,this);//塔向怪兽发射子弹
                time3=tmp;
            }
            else if(tmp-time4>1500)
            {
                controller.Shoot(collidingItem,this);
                time4=tmp;
            }
        }
        if(collidingItem->data(GD_Type) == GO_Bullet2)//2号子弹，表示被击中
        {
            tmpBlood-=2;
            //cout<< tmpBlood<<endl;
            if(tmpBlood<=0){ controller.deleteMonster(this); }
        }
    }

    if(flag) setResume();

}

void Monster::minusBlood()
{
    tmpBlood-=2;
    //cout<< tmpBlood<<endl;
    if(tmpBlood<=0){ controller.deleteMonster(this); }

}
void MonsterFrog::minusBlood()
{
    tmpBlood-=2;
    //cout<< tmpBlood<<endl;
    if(tmpBlood<=0){ controller.deleteMonster(this); }

}
void MonsterGhost::minusBlood()
{
    tmpBlood-=2;
    //cout<< tmpBlood<<endl;
    if(tmpBlood<=0){ controller.deleteMonster(this); }

}
void MonsterDino::minusBlood()
{
    tmpBlood-=2;
    //cout<< tmpBlood<<endl;
    if(tmpBlood<=0){ controller.deleteMonster(this); }

}
void MonsterBoss::minusBlood()
{
    tmpBlood-=2;
    //cout<< tmpBlood<<endl;
    if(tmpBlood<=0){ controller.deleteMonster(this); }

}

void MonsterFrog::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,MONSTER_SIZE*2,6);//绘制矩形
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        qreal rate = tmpBlood/sumBlood;//计算比例
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,rate*MONSTER_SIZE*2,6);//绘制矩形
    }



}


QRectF MonsterFrog::boundingRect() const
{
    return QRectF(-MONSTER_SIZE, -MONSTER_SIZE, MONSTER_SIZE*2, MONSTER_SIZE*2);//参数合适，有待调节

}


void MonsterGhost::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,MONSTER_SIZE*2,6);//绘制矩形
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,MONSTER_SIZE*2,6);//绘制矩形
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        qreal rate = tmpBlood/sumBlood;//计算比例
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,rate*MONSTER_SIZE*2,6);//绘制矩形
    }



}


QRectF MonsterGhost::boundingRect() const
{
    return QRectF(-MONSTER_SIZE, -MONSTER_SIZE, MONSTER_SIZE*2, MONSTER_SIZE*2);//参数合适，有待调节

}


void MonsterDino::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,MONSTER_SIZE*2,6);//绘制矩形
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        qreal rate = tmpBlood/sumBlood;//计算比例
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,rate*MONSTER_SIZE*2,6);//绘制矩形
    }



}


QRectF MonsterDino::boundingRect() const
{
    return QRectF(-MONSTER_SIZE, -MONSTER_SIZE, MONSTER_SIZE*2, MONSTER_SIZE*2);//参数合适，有待调节

}

void MonsterBoss::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
        painter->drawRect(-MONSTER_SIZE,-MONSTER_SIZE-8,MONSTER_SIZE*2,6);//绘制矩形
        painter->setBrush(QBrush(Qt::red, Qt::SolidPattern));
        qreal rate = tmpBlood/sumBlood;//计算比例
        painter->drawRect(-MONSTER_SIZE-10,-MONSTER_SIZE-50-8,rate*MONSTER_SIZE*3,6);//绘制矩形
    }



}


QRectF MonsterBoss::boundingRect() const
{
    return QRectF(-MONSTER_SIZE-10, -MONSTER_SIZE-50, MONSTER_SIZE*3, MONSTER_SIZE*3);//参数合适，有待调节

}


