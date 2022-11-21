#include "gamecontroller.h"
#include "monstertwo.h"
#include "tower.h"
#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene)
{
    timer.start( 1000/33 );//开启充当游戏循环的定时器，定时间隔是 1000 / 33 毫秒，也就是每秒 30（1000 / 33 = 30）帧
    //用于测试
    MonsterTwo* m=new MonsterTwo();
    scene.addItem(m);
    MoonTower* t=new MoonTower(100,300);
    scene.addItem(t);

    scene.installEventFilter(this);//添加了事件过滤器，以便监听键盘事件
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance())); //这里的advanced()函数需要重写（？）
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

        MonsterTwo* m=new MonsterTwo();
        scene.addItem(m);
    } else {
        exit(0);
    }
}
