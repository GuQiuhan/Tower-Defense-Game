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


void Monster::setPic()
{
    Pic=":/gif/bat.gif";
}

Monster::~Monster()
{

}

void Monster::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());
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
    if(index==tmp_path.size()-1)//到达路径终点
    {
        return true;
    }

    else
    {
        index++;
        //qreal dx=tmp_path[index].x()-tmp_path[index-1].x();
        //qreal dy=tmp_path[index].y()-tmp_path[index-1].y();
        tmp=tmp_path[index];
        //boundingRect().adjust(dx,dy,0,0);
        setPos(tmp.x(),tmp.y());
        //cout<<tmp.x()<<"," <<tmp.y()<<endl;

    }


    return false;

}

void Monster::advance(int step)
{
    if(!step) return;
    move();

}
