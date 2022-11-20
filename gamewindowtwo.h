#ifndef GAMEWINDOWTWO_H
#define GAMEWINDOWTWO_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "gamecontroller.h"

namespace Ui {
class GameWindowTwo;
}

class GameWindowTwo : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindowTwo(QWidget *parent = nullptr);
    ~GameWindowTwo();

private:
    Ui::GameWindowTwo *ui;
    QGraphicsScene *scene;
    //QGraphicsProxyWidget *labelProxy;//背景widget的代理
    GameController* gamecontroller;
    void InitBackground();
    void test();//用来调试地图路径坐标
};

#endif // GAMEWINDOWTWO_H
