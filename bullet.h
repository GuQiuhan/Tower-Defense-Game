#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsItem>

class bullet:public QGraphicsItem
{
private:
    QPointF src;
    QPointF dest;
    QMovie* movie;

public:
    bullet(QPointF s, QPointF d);

protected:
    QRectF boundingRect() const; //override
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget); //override


};

#endif // BULLET_H
