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
    bool move();
    void advance(int phase) override; //当调用scene.advance()函数时，会调用每一个item的advance函数
};

class Tower
{

};

#endif // TOWER_H
