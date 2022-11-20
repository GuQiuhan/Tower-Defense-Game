#include "gamecontroller.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
    timer.start( 1000/33 );//开启充当游戏循环的定时器，定时间隔是 1000 / 33 毫秒，也就是每秒 30（1000 / 33 = 30）帧

//	Food *a1 = new Food(0, -50);
//    scene.addItem(a1);

//    scene.addItem(snake);
     scene.installEventFilter(this);//添加了事件过滤器，以便监听键盘事件
//    //resume();
//    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
//   isPause = false;
}

GameController::~GameController()
{
}


void GameController::pause()//断开定时器的信号
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene,  SLOT(advance()));
}

void GameController::resume()//连接定时器的信号
{
    connect(&timer, SIGNAL(timeout()),
            &scene,  SLOT(advance()));
}
