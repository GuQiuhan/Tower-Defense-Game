#include "bullet.h"
#include <QPainter>
#include <QMovie>

static const qreal BULLET_SIZE=20;//子弹矩形的边长，合适待调整

bullet::bullet(QPointF s, QPointF d)
{
    movie = new QMovie(QString::fromStdString(":/gif/bullet1.gif"));
    movie->start();

    src=s;
    dest=d;

    setPos(s.x(),s.y());
}


QRectF bullet::boundingRect() const //override
{
    return QRectF(-BULLET_SIZE, -BULLET_SIZE,  BULLET_SIZE*2, BULLET_SIZE * 2 );

}

void bullet::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget) //override
{
    if (movie && movie->state() == QMovie::Running)
    {

        //QRectF bound = boundingRect().adjusted(-20, -20, 30, 30);
        painter->drawImage(boundingRect(), movie->currentImage());

    }
}
