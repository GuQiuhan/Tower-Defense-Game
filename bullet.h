#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>
#include "gamecontroller.h"

class bullet:public QGraphicsItem
{
private:
    QPointF src;
    QPointF dest;
    QPointF tmp;
    QMovie* movie;
    void advance(int s);
    bool move();
    GameController &controller;
public:
    bullet(QPointF s, QPointF d,GameController& g);

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override


};

#endif // BULLET_H
