#include "monster.h"
#include <QMovie>
#include <iostream>
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
    //connect(mMovie, SIGNAL(finished ()),this, SLOT(slot_movieFinish()));
    setPos(tmp.x(),tmp.y());//重制item坐标原点（x,y相对于scene坐标系）
    pause=false;
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

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //cout<<movie->currentFrameNumber()<<endl;
        painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
    }



}

QRectF Monster::boundingRect() const
{
    return QRectF(-MONSTER_SIZE, -MONSTER_SIZE, MONSTER_SIZE*2, MONSTER_SIZE*2);//参数合适，有待调节

}

bool Monster::move()
{
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

}


void MonsterFrog::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //cout<<movie->currentFrameNumber()<<endl;
        painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
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

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //cout<<movie->currentFrameNumber()<<endl;
        painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
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

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //cout<<movie->currentFrameNumber()<<endl;
        painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
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

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());//在bounding Rect内画图，若boundingRect大了，图形也就大了
        //cout<<movie->currentFrameNumber()<<endl;
        painter->drawRect(boundingRect());//可以画出相应的item的Rect大小
    }



}


QRectF MonsterBoss::boundingRect() const
{
    return QRectF(-MONSTER_SIZE-10, -MONSTER_SIZE-50, MONSTER_SIZE*3, MONSTER_SIZE*3);//参数合适，有待调节

}


