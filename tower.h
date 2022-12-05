#ifndef TOWER_H
#define TOWER_H
#include <vector>
#include <QGraphicsItem>
#include "gamecontroller.h"
using namespace std;

#ifndef GLOBAL
#define GLOBAL
enum GameObjectsData {
    GD_Type
};

enum GameObjectTypes {
    GO_Tower,
    GO_Monster,
    GO_Bullet,//怪兽打塔的子弹
    GO_Bullet2,//塔打怪兽的子弹
    GO_GunTower,
};
#endif

//第一个塔：月亮塔
class MoonTower : public QGraphicsItem
{
public:
    MoonTower(qreal x, qreal y,GameController& c);//qreal默认为double

    //QPainterPath shape() const;

private:
    QMovie * movie;
    long long time1;
    long long time2;

    int  sumBlood;
    int tmpBlood;


protected:
    QPointF tmp;//当前像素位置
    void advance(int phase) override; //当调用scene.advance()函数时，会调用每一个item的advance函数

    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
    void handleCollisions();
    GameController& controller;
    //QPainterPath shape() const override;
};

class GunTowerOne:public MoonTower
{
    QString path;
    long long time1;
    long long time2;

public:
    GunTowerOne(qreal x, qreal y,GameController& c)
        :MoonTower(x,y,c)
    {
        path=":/image/tower4_v1.jpg";
        setData(GD_Type, GO_GunTower);
        setPos(x, y);
        time1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
        time2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    }
protected:
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
    QPainterPath shape() const override;
   // void handleCollisions();
    //void advance(int phase) override;
};


class GunTowerTwo:public GunTowerOne
{
    QString path;
    long long time1;
    long long time2;

public:
    GunTowerTwo(qreal x, qreal y,GameController& c)
        :GunTowerOne(x,y,c)
    {
        path=":/image/tower5_v1.jpg";
        setData(GD_Type, GO_GunTower);
        setPos(x, y);
        time1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
        time2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
    QPainterPath shape() const override;
   // void handleCollisions();
    //void advance(int phase) override;
};

class GunTowerThree:public GunTowerOne
{
    QString path;
    long long time1;
    long long time2;

public:
    GunTowerThree(qreal x, qreal y,GameController& c)
        :GunTowerOne(x,y,c)
    {
        path=":/image/tower4_v2.jpg";
        setData(GD_Type, GO_GunTower);
        setPos(x, y);
        time1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
        time2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
    QPainterPath shape() const override;
    //void handleCollisions();
    //void advance(int phase) override;
};

class GunTowerFour:public GunTowerOne
{
    QString path;
    long long time1;
    long long time2;

public:
    GunTowerFour(qreal x, qreal y,GameController& c)
        :GunTowerOne(x,y,c)
    {
        path=":/image/tower5_v2.jpg";
        setData(GD_Type, GO_GunTower);
        setPos(x, y);
        time1=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();//获取系统时间，单位为毫秒
        time2=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
    QPainterPath shape() const override;
    //void handleCollisions();
    //void advance(int phase) override;
};
#endif // TOWER_H
