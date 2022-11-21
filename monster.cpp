#include "monster.h"
#include <QMovie>
#include <iostream>
using namespace std;

static const qreal MONSTER_SIZE=30;//怪兽矩阵的边长

Monster::Monster()//基类Monster
{
    setPic();//创建时需要确定图片

    movie = new QMovie(QString::fromStdString(Pic));
    movie->start();
    //connect(mMovie, SIGNAL(finished ()),this, SLOT(slot_movieFinish()));
    setPos(860,100);//重制item坐标原点（x,y相对于scene坐标系）
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
