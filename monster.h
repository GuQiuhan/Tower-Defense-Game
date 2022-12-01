#ifndef MONSTERTWO_H
#define MONSTERTWO_H


#include "structures.h"
#include <vector>
#include <QGraphicsItem>
#include <QPainter>
using namespace std;

class GameController;


//monster的第二种实现方式
//继承QGraphicsItem来实现
class Monster:public QGraphicsItem
{
private:
    vector<QPointF> tmp_path;//当前路径（随机选择）
    QPointF tmp;//当前像素位置
    int index;//当前位置于路径中的下标
    string Pic;//所用的gif路径
    QMovie * movie;//构造gif图片所需
    bool pause;//遇到近战塔需要停止,只有在false时才可以移动
    bool move();//到达终点则返回true
    GameController &controller;
    void advance(int s);//必须重载！用于计时器刷新时调用
public:
    Monster(vector<QPointF> p,GameController & controller);//创建时需要给出路径
    Monster(Monster& m);//拷贝构造函数
    //Monster();
    virtual void setPic();//虚函数,子类中需要重写以确定自己的图片
    virtual ~Monster();

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override


};

#endif // MONSTERTWO_H
