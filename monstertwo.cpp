#include "monstertwo.h"
#include <QMovie>
#include <iostream>
using namespace std;

MonsterTwo::MonsterTwo()//基类Monster
{
    setPic();//创建时需要确定图片

    movie = new QMovie(QString::fromStdString(Pic));
    movie->start();
    //connect(mMovie, SIGNAL(finished ()),this, SLOT(slot_movieFinish()));
    setPos(860,0);//重制item坐标原点（x,y相对于scene坐标系）
}


void MonsterTwo::setPic()
{
    Pic=":/gif/bat.gif";
}

MonsterTwo::~MonsterTwo()
{

}

void MonsterTwo::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());
        //cout<<movie->currentFrameNumber()<<endl;
        painter->drawRect(-20,-20,50,50);//可以画出相应的item的Rect大小
    }

}

QRectF MonsterTwo::boundingRect() const
{
    return QRectF(-20, -20, 50, 50);//

}
