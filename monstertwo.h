#ifndef MONSTERTWO_H
#define MONSTERTWO_H


#include "structures.h"
#include <vector>
#include <QGraphicsItem>
#include <QPainter>
using namespace std;


//monster的第二种实现方式
//继承QGraphicsItem来实现
class MonsterTwo:public QGraphicsItem
{
private:
    vector<vector<QPointF>> path;//怪兽的所有路径
    vector<QPointF> tmp_path;//当前路径（随机选择）
    QPointF tmp;//当前像素位置
    string Pic;//所用的gif路径
    QMovie * movie;


public:
    MonsterTwo();//创建时需要给出路径
    virtual void setPic();//虚函数,子类中需要重写以确定自己的图片
    virtual ~MonsterTwo();

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override


};

#endif // MONSTERTWO_H
