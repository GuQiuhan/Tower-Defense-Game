#include "gamewindowtwo.h"
#include "ui_gamewindowtwo.h"
#include <QLabel>
#include <QMovie>
#include "monstertwo.h"
#include <iostream>
#include <QTimer>
#include <QPushButton>
using namespace std;

GameWindowTwo::GameWindowTwo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindowTwo),
    scene(new QGraphicsScene(this)),
    gamecontroller(new GameController(*scene,this))
{
    ui->setupUi(this);

    InitBackground();

    //添加怪兽
    MonsterTwo* m=new MonsterTwo();
    scene->addItem(m);
    //m->setZValue(100000);
    //m->setParentItem(labelProxy);
    //m->stackBefore(labelProxy);

    test();






}

void GameWindowTwo::InitBackground()
{
    scene->setSceneRect(0, 0, 900, 550);//设置坐标系，此时坐标（0，0）在窗口左上角
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("background: transparent");
    //一定要设置透明背景！将label置于底层，这样子scene里的item才可以露出来，底下的background也可以看见

    //添加背景到scene
    //由于背景是gif,所以使用scene->addWidget
    QLabel* label=new QLabel(this);
    label->setGeometry(0,0,910,560);
    QMovie *movie = new QMovie(":/image/map2.gif");
    label->setMovie(movie);// 在标签中添加动画
    label->setScaledContents(true);
    label->lower();//一定要这句代码置于底层！否则看不见view
    movie->start();
    // 将label添加到场景中
    //labelProxy= scene->addWidget(label);//scene->addWidget返回一个代理

}
GameWindowTwo::~GameWindowTwo()//释放内存
{
    //labelProxy=NULL;
    //delete labelProxy;//这里删除会导致程序崩溃吗？
    delete scene;
    delete ui;
}

void GameWindowTwo::test()
{
    QPen pen;
    pen.setWidth(2);
    pen.setColor(Qt::black);
    //第一条路
    scene->addLine(330,0,330,100);
    scene->addLine(330,100,300,125);
    scene->addLine(300,125,160,125);
    scene->addLine(160,125,110,175);
    scene->addLine(110,175,110,430);
    scene->addLine(110,430,160,480);
    scene->addLine(160,480,300,480);
    scene->addLine(300,480,340,450);
    scene->addLine(340,450,480,450);
    scene->addLine(480,450,530,475);
    scene->addLine(530,475,910,475);
    //(330,0)
    //(330,100)
    //(300,125)
    //(160,125)
    //(110,175)
    //(110,430)
    //(160,480)
    //(300,480)
    //(340,450)
    //(480,450)
    //(530,475)
    //(910,475)

    //第二条路
    scene->addLine(860,0,860,260);
    scene->addLine(860,260,825,305);
    scene->addLine(825,305,700,305);
    scene->addLine(700,305,650,340);
    scene->addLine(650,340,650,475);
    scene->addLine(650,475,910,475);
    //(860,0)
    //(860,260)
    //(825,305)
    //(700,305)
    //(650,340)
    //(650,475)
    //(910,475)



}
