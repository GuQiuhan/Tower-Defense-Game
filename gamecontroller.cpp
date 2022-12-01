#include "gamecontroller.h"
#include "monster.h"
#include "tower.h"
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <vector>
#include <iostream>
using namespace std;
#include "bullet.h"

//全局变量，map1中怪兽的所有路径
vector<vector<QPointF>> MonsterPaths={
    {
        QPointF(330,0),
        QPointF(330,100),
        QPointF(300,125),
        QPointF(160,125),
        QPointF(110,175),
        QPointF(110,430),
        QPointF(160,480),
        QPointF(300,480),
        QPointF(340,440),
        QPointF(480,440),
        QPointF(530,475),
        QPointF(910,475)
    },
    {
        QPointF(870,0),
        QPointF(870,260),
        QPointF(825,305),
        QPointF(700,305),
        QPointF(650,340),
        QPointF(650,475),
        QPointF(910,475)
    }
};

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{   
    scene.installEventFilter(this);//添加了事件过滤器，以便监听键盘事件

    timer.start( 1000/40 );//开启充当游戏循环的定时器，定时间隔是 1000 / 40 毫秒，也就是每秒40帧
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance())); //这里的advanced()函数需要重写（？），计时器开始运行即不断调用各个类成员的advance()函数

    Monstertimer.start(5000);//每5秒产生一个怪物
    connect(&Monstertimer, SIGNAL(timeout()), this, SLOT(addMonster()));

    //用于测试
    MoonTower* t=new MoonTower(100,300);
    scene.addItem(t);
    bullet* b=new bullet(QPointF(100,100),QPointF(200,200));
    scene.addItem(b);




    isPause = false;
}

GameController::~GameController()//释放内存
{
    delete resumeAction;
}


void GameController::pause()//断开定时器的信号
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene,  SLOT(advance()));
    isPause = true;
    setResume();
}

void GameController::resume()//连接定时器的信号
{
    connect(&timer, SIGNAL(timeout()),
            &scene,  SLOT(advance()));

    isPause = false;
    setResume();
}

void GameController :: setResume(){
    if(isPause == true){
        resumeAction->setEnabled(true);
    }else{
        resumeAction->setEnabled(false);
    }
}
bool GameController::eventFilter(QObject *object, QEvent *event)//事件过滤器
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}

void GameController::handleKeyPressed(QKeyEvent *event)//处理键盘事件
{
//    if (!isPause)
//        switch (event->key()) {
//            case Qt::Key_Left:
//                snake->setMoveDirection(Snake::MoveLeft);
//                break;
//            case Qt::Key_Right:
//                snake->setMoveDirection(Snake::MoveRight);
//                break;
//            case Qt::Key_Up:
//                snake->setMoveDirection(Snake::MoveUp);
//                break;
//            case Qt::Key_Down:
//                snake->setMoveDirection(Snake::MoveDown);
//                break;
//            case Qt::Key_Space:
//                pause();
//                break;
//        }
//    else resume();
    switch (event->key()) {  //空格键可控制游戏是否暂停
        case Qt::Key_Space:
            if(isPause)
                resume();
            else
                pause();
            break;
    }

}

void GameController::gameOver() //游戏结束，计时器停止
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) {
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));//重新开始游戏
        scene.clear();

        srand((unsigned)time(NULL));
        Monster* m=new Monster(MonsterPaths[rand()%2],*this);
        scene.addItem(m);
    } else {
        exit(0);
    }
}

void GameController::addMonster()
{
    srand((unsigned)time(NULL));
    int a=rand();
    //cout<< a<<endl;
    Monster* m=new Monster(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
    scene.addItem(m);
    monsters.push_back(m);
}
