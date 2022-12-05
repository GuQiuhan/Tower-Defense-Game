#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include "gamecontroller.h"

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

class bullet:public QGraphicsItem
{
private:
    QPointF src;
    QPointF dest;

    QMovie* movie;


public:
    bullet(QPointF s, QPointF d,GameController& g);

protected:
    void advance(int s);
    bool move();
    void handleCollisions();
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override

    GameController &controller;
    QPointF tmp;

};

class bulletTwo:public bullet
{
    QMovie* movie;
public:
    bulletTwo(QPointF s, QPointF d,GameController& g)
        :bullet(s,d,g)
    {
         setData(GD_Type, GO_Bullet2);
         movie = new QMovie(QString::fromStdString(":/gif/bullet2.gif"));
         movie->start();
    }

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override
    void advance(int s);
    void handleCollisions();

};

#endif // BULLET_H
