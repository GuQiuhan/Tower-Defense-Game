#ifndef MONSTERTWO_H
#define MONSTERTWO_H


#include "structures.h"
#include <vector>
#include <QGraphicsItem>
#include <QPainter>
#include <iostream>
#include <QMovie>
#include <string>
using namespace std;

class GameController;


//monster的第二种实现方式
//继承QGraphicsItem来实现
class Monster:public QGraphicsItem
{
private:
   // vector<QPointF> tmp_path;//当前路径（随机选择）
    QPointF tmp;//当前像素位置
    int index;//当前位置于路径中的下标
    string Pic;//所用的gif路径,派生类中要使用
    QMovie * movie;//构造gif图片所需
    bool pause;//遇到近战塔需要停止,只有在false时才可以移动

    void advance(int s);//必须重载！用于计时器刷新时调用

public:
    vector<QPointF> tmp_path;//当前路径（随机选择）
    Monster(vector<QPointF> p,GameController & controller);//创建时需要给出路径
    Monster(Monster& m);//拷贝构造函数
    //Monster();
    virtual void setPic();//虚函数,子类中需要重写以确定自己的图片
    virtual ~Monster();


    bool isAlive(){return tmpBlood>0;}
protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override
    void handleCollisions();
    GameController &controller;
    bool move();//到达终点则返回true
    void setPause(){pause=true;}
    void setResume(){pause=false;}
    long long time1;//两个计时器，一起用于发射子弹的时间间隔控制
    long long time2;
    long long time3;//两个计时器，一起用于塔发射子弹的时间间隔控制
    long long time4;
    qreal sumBlood;//总血量
    qreal tmpBlood;//当前血量

};


class MonsterFrog:public Monster
{
private:
    string Pic;
    QMovie * movie;//构造gif图片所需
    //qreal sumBlood;//总血量
    //qreal tmpBlood;//当前血量
public:

    MonsterFrog(vector<QPointF> p,GameController & controller)
        :Monster(p,controller)
    {
        setPic();
        movie = new QMovie(QString::fromStdString(Pic));
        movie->start();
       // sumBlood=10;
       // tmpBlood=10;

    }

    ~MonsterFrog(){delete movie;}

    void setPic(){Pic=":/gif/frog.gif";}

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override

};


class MonsterGhost:public Monster
{
private:
    string Pic;
    QMovie * movie;//构造gif图片所需
    //qreal sumBlood;//总血量
    //qreal tmpBlood;//当前血量
public:

    MonsterGhost(vector<QPointF> p,GameController & controller)
        :Monster(p,controller)
    {
        setPic();
        movie = new QMovie(QString::fromStdString(Pic));
        movie->start();
        //sumBlood=10;
        //tmpBlood=10;

    }

    ~MonsterGhost(){delete movie;}

    void setPic(){Pic=":/gif/ghost.gif";}

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override

};


class MonsterDino:public Monster
{
private:
    string Pic;
    QMovie * movie;//构造gif图片所需
    //qreal sumBlood;//总血量
    //qreal tmpBlood;//当前血量
public:

    MonsterDino(vector<QPointF> p,GameController & controller)
        :Monster(p,controller)
    {
        setPic();
        movie = new QMovie(QString::fromStdString(Pic));
        movie->start();
       // sumBlood=10;
        //tmpBlood=10;

    }

    ~MonsterDino(){delete movie;}

    void setPic()
    {
        //srand((unsigned)time(NULL));//不可以用时间做随机，因为每5秒更新一次，这时候根据事件产生的随机数就不随机了
        int a=rand()%5;
        if(a==0) a++;
        //cout << a<<endl;
        Pic=":/gif/Dino"+std::to_string(a)+".gif";//随机产生一个小恐龙
    }

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override

};

class MonsterBoss:public Monster
{
private:
    string Pic;
    QMovie * movie;//构造gif图片所需
    //qreal sumBlood;//总血量
    //qreal tmpBlood;//当前血量

public:

    MonsterBoss(vector<QPointF> p,GameController & controller)
        :Monster(p,controller)
    {
        setPic();
        movie = new QMovie(QString::fromStdString(Pic));
        movie->start();
        //sumBlood=20;
        //tmpBlood=20;

    }

    ~MonsterBoss(){delete movie;}

    void setPic()
    {
        Pic=":/gif/skeleton.gif";//随机产生一个小恐龙
    }


protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override

};

#endif // MONSTERTWO_H
