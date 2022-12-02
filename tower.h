#ifndef TOWER_H
#define TOWER_H
#include <vector>
#include <QGraphicsItem>
using namespace std;

//第一个塔：月亮塔
class MoonTower : public QGraphicsItem
{
public:
    MoonTower(qreal x, qreal y);//qreal默认为double

    //QPainterPath shape() const;

private:
    QMovie * movie;
    QPointF tmp;//当前像素位置
    void advance(int phase) override; //当调用scene.advance()函数时，会调用每一个item的advance函数

protected:
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
};

class GunTowerOne:public MoonTower
{
    QString path;
public:
    GunTowerOne(qreal x, qreal y)
        :MoonTower(x,y)
    {
        path=":/image/tower4_v1.jpg";
    }
protected:
    QRectF boundingRect() const ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
};


class GunTowerTwo:public GunTowerOne
{
    QString path;
public:
    GunTowerTwo(qreal x, qreal y)
        :GunTowerOne(x,y)
    {
        path=":/image/tower5_v1.jpg";
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;
};

class GunTowerThree:public GunTowerOne
{
    QString path;
public:
    GunTowerThree(qreal x, qreal y)
        :GunTowerOne(x,y)
    {
        path=":/image/tower4_v2.jpg";
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;

};

class GunTowerFour:public GunTowerOne
{
    QString path;
public:
    GunTowerFour(qreal x, qreal y)
        :GunTowerOne(x,y)
    {
        path=":/image/tower5_v2.jpg";
    }

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) ;

};
#endif // TOWER_H
