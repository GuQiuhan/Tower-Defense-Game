#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "roles.h"
#include <fstream>
#include <iostream>
#include <QImageReader>
#include <QTimer>
#include "findmonsterway.h"
#include "time.h"
using namespace std;

GameWindow::GameWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
}

GameWindow::~GameWindow()
{
    delete ui;
}


GameWindow::GameWindow(string path)//从文件读入地图
{
    MonsterNumber=0;//初始化怪物数量
    setFixedSize(1040, 640);//初始化窗口大小，13x8*80（基本地图扩大80倍）
    setWindowTitle("GameWindow");

    //读入地图基本数据
    loadMap(path);//初始地图
    MonsterWays=FindMonsterWay().FindWay(basic_map);//初始化怪兽的所有路径
    /**cout<< "Monster Ways:"<<endl;
    for(int i=0; i<MonsterWays.size(); ++i)
        {
            for(int j=0; j<MonsterWays[i].size(); ++j)
            {
                cout<<MonsterWays[i][j].x<<","<<MonsterWays[i][j].y<<" ";
            }
            cout<< endl;
        }
        cout<< "ok"<<endl;
    **/

    //启动monster计时器
    timer_monster = new QTimer(this);
    connect(timer_monster, SIGNAL(timeout()), this, SLOT(addMonster()));
    timer_monster->start(1000);

    //游戏刷新计时器
    timer_game = new QTimer(this);
    connect(timer_game, SIGNAL(timeout()), this, SLOT(refreshGameWindow()));
    timer_game->start(100);




    update();
}


void GameWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    drawMap(painter);       //画出地图

//    drawBull(painter);      //画出子弹
//    drawEnemy(painter);     //画出怪物
//    drawTower(painter);     //画出防御塔
//    drawHitEffect(painter); //画出命中效果

//    drawSelectionFrame(painter);    //画出选择框

//    if(victoryFlag)         //画出游戏胜利提示
//        painter.setPen(QPen(Qt::white)), painter.setFont(QFont("楷体", 110)), painter.drawText(176, 350, "游戏胜利");

}


void GameWindow::loadMap(string path)
{
    ifstream fin;
    fin.open(path);
    if(fin.fail()) cout<< "Fail to open the file:"<<path <<endl;
    for(int i=0; i<8; ++i)
    {
        for(int j=0; j<13; ++j)
        {
            fin >> basic_map[i][j];
        }
    }
    fin.close();

    cout<< "map:"<<endl;
    for(int i=0; i<8; ++i)
    {
        for(int j=0; j<13; ++j)
        {
            cout<<basic_map[i][j]<<" ";
        }

        cout<<endl;
    }
    cout<< "ok."<<endl;

}


void GameWindow::drawMap(QPainter &painter)
{

    for(int j = 0; j < 8; j++)
    {
            for(int i = 0; i < 13; i++)
            {
                //采用QImageReader加速读取
                QImageReader reader;
                QImage image;
                reader.setDecideFormatFromContent(true);
                reader.setScaledSize(QSize(mapBlockLen, mapBlockLen));
                reader.setFileName(QString::fromStdString(Pics[basic_map[j][i]]));
                if (reader.canRead())
                {
                    if (!reader.read(&image))
                    {
                        QImageReader::ImageReaderError error = reader.error();
                        QString strError = reader.errorString();
                        printf("last error:%s\n", strError.toStdString().c_str());
                        return;
                    }
                }
                painter.drawPixmap(i * mapBlockLen, j * mapBlockLen, mapBlockLen, mapBlockLen, QPixmap::fromImage(image));

                //painter.drawPixmap(i * mapBlockLen, j * mapBlockLen, mapBlockLen, mapBlockLen, QPixmap(QString::fromStdString(Pics[basic_map[j][i]])));



            }

   }
}

void GameWindow::addMonster()//根据已添加怪兽的数量来添加不同级别的怪兽，怪兽越多添加的级别越高，路径随机生成
{
    if(MonsterNumber<5)//游戏初始，怪兽少、产出速度慢
    {
        //生成一个初级怪
        srand((unsigned)time(NULL));
        vector<Pos>path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(basic_Monster(path));
        MonsterNumber+=1;
        cout<< "Now Monster Number:"<<MonsterNumber<<endl;
        return;
    }
    else if(MonsterNumber<10)
    {
        //生成一个初级怪和一个高级怪
        srand((unsigned)time(NULL));
        vector<Pos>path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(basic_Monster(path));

        srand((unsigned)time(NULL));
        path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(advanced_Monster(path));

        MonsterNumber+=2;
        cout<< "Now Monster Number:"<<MonsterNumber<<endl;
        return;
    }
    else if(MonsterNumber<15)
    {
        //生成两个初级怪和两个高级怪
        srand((unsigned)time(NULL));
        vector<Pos>path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(basic_Monster(path));

        srand((unsigned)time(NULL));
        path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(advanced_Monster(path));

        srand((unsigned)time(NULL));
        path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(basic_Monster(path));

        srand((unsigned)time(NULL));
        path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(advanced_Monster(path));

        MonsterNumber+=4;
        cout<< "Now Monster Number:"<<MonsterNumber<<endl;
        return;
    }
    else
    {
        //生成两个高级怪和一个boss
        srand((unsigned)time(NULL));
        vector<Pos>path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(advanced_Monster(path));

        srand((unsigned)time(NULL));
        path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(advanced_Monster(path));

        srand((unsigned)time(NULL));
        path=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
        Monsters.push_back(Boss(path));

        MonsterNumber+=3;
        cout<< "Now Monster Number:"<<MonsterNumber<<endl;
        return;
    }

}

void GameWindow::refreshGameWindow()
{
    //攻击怪兽
    for(auto tower : Towers)
    {
        vector<Monster> tempMonster;
        for(auto &monster : Monsters)  //遍历敌人数组，将防御塔范围内的所有敌人插入到临时敌人数组中
            if(tower.inRange(monster))
                tempMonster.push_back(monster);

        tower.Attack(tempMonster); //把范围内的敌人作为参数传递给防御塔
    }


}

//画出选择框
void GameWindow::drawSelectionFrame(QPainter& painter)
{
    if(!selectionFrame.getDisplay()) return;    //选择框显示状态为假则返回

    //画出选择框
    painter.drawPixmap(selectionFrame.getCoor().x, selectionFrame.getCoor().y,
       selectionFrame.getSelSideLength(), selectionFrame.getSelSideLength(),
       QPixmap("../PictureMaterial/Check_the_tower_effect.png"));

    //画出选中标志2
    painter.drawPixmap(selectionFrame.getCoor().x + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
       selectionFrame.getCoor().y + ((selectionFrame.getSelSideLength() - mapBlockLen) >> 1),
       mapBlockLen, mapBlockLen, QPixmap("../PictureMaterial/Check_the_tower_effect.png"));

    //画出子按钮
    for(int i = 0; i < 4; i++)
    {
        painter.drawPixmap(selectionFrame.getChildButtonArr()[i].x, selectionFrame.getChildButtonArr()[i].y,
            selectionFrame.getButSideLength(), selectionFrame.getButSideLength(),
            QPixmap(selectionFrame.getChildButtonArr()[i].picturePath));

        //画出防御塔图片
        painter.drawPixmap(selectionFrame.getChildButtonArr()[i].x + 10, selectionFrame.getChildButtonArr()[i].y + 10,
            selectionFrame.getButSideLength() - 20, selectionFrame.getButSideLength() - 20,
            QPixmap(selectionFrame.getTowerPicturePathArr()[i]));
    }
}

