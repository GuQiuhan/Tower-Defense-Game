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
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    QPainterPath shape() const;

private:
    QMovie * movie;
};

class Tower
{

};

#endif // TOWER_H
