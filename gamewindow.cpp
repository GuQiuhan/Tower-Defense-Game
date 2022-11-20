#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <fstream>
#include <iostream>
#include <QImageReader>
#include <QTimer>
#include "findmonsterway.h"
#include "time.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMovie>
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
    setFixedSize(910, 560);//初始化窗口大小，13x8*80（基本地图扩大80倍）
    setWindowTitle("GameWindow");
    loadmap(path);
    //playMusic();//因为版本原因暂时无法实现

    MonsterWays=FindMonsterWay().FindWay(basic_map);//初始化怪兽的所有路径

    //启动monster计时器
    timer_monster = new QTimer(this);
    connect(timer_monster, SIGNAL(timeout()), this, SLOT(addMonster()));
    timer_monster->start(10000);//每10秒增加一波怪兽

   //测试，生成一个怪兽
    srand((unsigned)time(NULL));
   vector<Pos>p=MonsterWays[rand()%MonsterWays.size()];//随机选中一个路径
    Monsters.push_back(basic_Monster(p));


    QTimer* timer_game = new QTimer(this);
    connect(timer_game, SIGNAL(timeout()), this, SLOT(gaming()));
    timer_game->start(100);
}


void GameWindow::loadmap(string path)
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


void GameWindow::paintEvent(QPaintEvent*)//重载重新绘画函数，系统刷新时自动调用
{
    QPainter painter(this);

    drawMap(painter); //画出地图
    drawMonster(painter);
}

void GameWindow::drawMap(QPainter& painter)
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

//因为版本原因暂时无法实现
void GameWindow::playMusic()
{
    QMediaPlayer* player = new QMediaPlayer();
    //connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile(":/images/music1.mp3"));
    player->setVolume(50);  //音量
    player->play();
}


void GameWindow::drawMonster(QPainter& painter)   //画出敌人和血条
{
    for(auto m : Monsters)
    {
//        QLabel *label = new QLabel();
//        QMovie *movie = new QMovie(QString::fromStdString(m.getPic()));

//        label->move(m.getPos().y-35, m.getPos().x-35);
//        QSize s(m.getWidth(), m.getHeight());
//        movie->setScaledSize(s);
//        label->setMovie(movie); // 1. 设置要显示的 GIF 动画图片
//        movie->start();         // 2. 启动动画
//        label->show();

        QPixmap pix;
        pix.load(QString::fromStdString(m.getPic()));
        //painter.drawRect(m.getPos().x, m.getPos().y - 10, m.getWidth() * (m.getHealth() / enemy->getOrihealth()), 6);    //画出敌人血条
        painter.drawPixmap(m.getPos().y-35, m.getPos().x-35, m.getWidth(), m.getHeight(), pix);
        //cout<<m.getPos().x<<" "<< m.getPos().y<<endl;
    }
    //cout<<"monster"<<endl;
}

void GameWindow::gaming()
{
    for(vector<Monster>::iterator it= Monsters.begin();it!=Monsters.end(); ++it)//注意这里怪兽的移动需要用指针来
    {

        it->move();

        //cout<<m.getPos().x<<" "<< m.getPos().y<<endl;
    }
    update();
}

