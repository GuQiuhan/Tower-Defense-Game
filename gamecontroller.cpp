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
#include <QDebug>

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

    Monstertimer.start(3000);//每5秒产生一个怪物
    //开局先产生一个怪物
    srand((unsigned)time(NULL));
    int a=rand();
    //MonsterFrog* m=new MonsterFrog(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
    //scene.addItem(m);
    //monsters.push_back(m);
    MonsterNumberChange();
    //打开怪物生成计时器
    connect(&Monstertimer, SIGNAL(timeout()), this, SLOT(addMonster()));

    Round=0;
    //用于测试
    MoonTower* t=new MoonTower(150,400,*this);
    towers.push_back(t);
    //MoonTower* t=new MoonTower(330,100);
    //qDebug()<<t->x()<<","<<t->y();
    //t->setFlags(QGraphicsItem::ItemIsMovable);//实现图元的可拖动
    scene.addItem(t);
//    bullet* b=new bullet(QPointF(0,100),QPointF(900,200),*this);
//    scene.addItem(b);
//    bullets.push_back(b);




    isPause = false;
}

GameController::~GameController()//释放内存
{
    delete resumeAction;
}


void GameController::pause()//断开定时器的信号
{
    //断开所有计时器
    disconnect(&timer, SIGNAL(timeout()),&scene,  SLOT(advance()));
    disconnect(&Monstertimer, SIGNAL(timeout()), this, SLOT(addMonster()));
    isPause = true;
    setResume();
}

void GameController::resume()//连接定时器的信号
{
    connect(&timer, SIGNAL(timeout()),&scene,  SLOT(advance()));
    connect(&Monstertimer, SIGNAL(timeout()), this, SLOT(addMonster()));
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
    disconnect(&Monstertimer, SIGNAL(timeout()), this, SLOT(addMonster()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) {

        for( vector<bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++ )
        {
            delete *it;//释放内存
            *it=NULL;
        }
        for( vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); it++ )
        {
            delete *it;//释放内存
            *it=NULL;
        }
        for( vector<MoonTower*>::iterator it = towers.begin(); it != towers.end(); it++ )
        {
            delete *it;//释放内存
            *it=NULL;
        }
        monsters.clear();
        bullets.clear();
        towers.clear();
        scene.clear();
        Round++;
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));//重新开始游戏

        //开局先产生一个怪物
        int a=rand();
        Monster* m=new Monster(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
        scene.addItem(m);
        monsters.push_back(m);
        MonsterNumberChange();
        //打开怪物生成计时器
        connect(&Monstertimer, SIGNAL(timeout()), this, SLOT(addMonster()));

    } else {
        exit(0);
    }
}

void GameController::addMonster()
{
    //srand((unsigned)time(NULL));
    int a=rand();
    int n=monsters.size();
    //cout<< a<<endl;
    if(n<2)
    {
        Monster* m=new Monster(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
        scene.addItem(m);
        monsters.push_back(m);
    }
    else if(n<3)
    {
        MonsterFrog* m=new MonsterFrog(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
        scene.addItem(m);
        monsters.push_back(m);
    }
    else if(n<5)
    {
        MonsterGhost* m=new MonsterGhost(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
        scene.addItem(m);
        monsters.push_back(m);
    }
    else if(n<10)
    {
        MonsterDino* m=new MonsterDino(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
        scene.addItem(m);
        monsters.push_back(m);
    }
    else if(n<15)
    {
        int x=rand();
        x=x%4;
        switch(x){
            case 0:
            {
                Monster* m=new Monster(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
                scene.addItem(m);
                monsters.push_back(m);
                break;
            }
            case 1:
            {
                MonsterFrog* m=new MonsterFrog(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
                scene.addItem(m);
                monsters.push_back(m);
                break;
            }
            case 2:
            {
                MonsterGhost* m=new MonsterGhost(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
                scene.addItem(m);
                monsters.push_back(m);
                break;
            }
            case 3:
            {
                MonsterDino* m=new MonsterDino(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
                scene.addItem(m);
                monsters.push_back(m);
                break;
            }
        }
    }

    else if(n==15)//产生最终的boss
    {
        MonsterBoss* m=new MonsterBoss(MonsterPaths[a%2],*this);//初始化一个怪兽，怪兽随机选择一个敌人，初始化时分配控制器
        scene.addItem(m);
        monsters.push_back(m);
    }

    MonsterNumberChange();//发出信号
}


void GameController::addTower(QString type,QPointF pos)
{
    if(type=="MoonTower")
    {
        MoonTower* t=new MoonTower(pos.x(),pos.y(),*this);

        t->setFlags(QGraphicsItem::ItemIsMovable);//实现图元的可拖动
        scene.addItem(t);
    }
    else if(type=="GunTower1")
    {
        GunTowerOne* t=new GunTowerOne(pos.x(),pos.y(),*this);

        t->setFlags(QGraphicsItem::ItemIsMovable);//实现图元的可拖动
        scene.addItem(t);
    }
    else if(type=="GunTower2")
    {
        GunTowerTwo* t=new GunTowerTwo(pos.x(),pos.y(),*this);

        t->setFlags(QGraphicsItem::ItemIsMovable);//实现图元的可拖动
        scene.addItem(t);
    }
    else if(type=="GunTower3")
    {
        GunTowerThree* t=new GunTowerThree(pos.x(),pos.y(),*this);

        t->setFlags(QGraphicsItem::ItemIsMovable);//实现图元的可拖动
        scene.addItem(t);
    }
    else if(type=="GunTower4")
    {
        GunTowerFour* t=new GunTowerFour(pos.x(),pos.y(),*this);

        t->setFlags(QGraphicsItem::ItemIsMovable);//实现图元的可拖动
        scene.addItem(t);
    }

}

int GameController::getRound()
{
    return Round;
}

//void GameController::MonsterNumberChange(int i)
//{
//    MonsterNumber+=i;
//}

int GameController::getMonsterNumber()
{
    int sum=0;
    for(int i=0; i<monsters.size();++i)
    {
        if(monsters[i]->isAlive()) sum+=1;
    }
    return sum;

}

void GameController::deleteBullet(bullet* b)
{
    scene.removeItem(b);//删除图元
    for( vector<bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++ )
    {
        if( *it == b )
        {
           delete *it;//释放内存
            *it=NULL;
           it= bullets.erase(it);
           break;
        }
    }


}

void GameController::deleteMonster(Monster* m)
{
    scene.removeItem(m);//删除图元
    for( vector<Monster*>::iterator it = monsters.begin(); it != monsters.end(); it++ )
    {
        if( *it == m )
        {
           delete *it;//释放内存
            *it=NULL;
           it= monsters.erase(it);
           break;
        }
    }


}

void GameController::deleteTower(MoonTower* t)
{
    scene.removeItem(t);//删除图元
    for( vector<MoonTower*>::iterator it = towers.begin(); it != towers.end(); it++ )
    {
        if( *it == t )
        {
           delete *it;//释放内存
            *it=NULL;
           it= towers.erase(it);
           break;
        }
    }


}


void GameController::Shoot(Monster* m,QGraphicsItem* t)
{
    bullet* b=new bullet(m->pos(),t->pos(),*this);//发射一号子弹
    scene.addItem(b);
    bullets.push_back(b);
}

void GameController::Shoot(QGraphicsItem* t,Monster* m)
{
    bulletTwo* b=new bulletTwo(t->pos(),m->pos(),*this);//发射2号子弹
    scene.addItem(b);
    bullets.push_back(b);
}
