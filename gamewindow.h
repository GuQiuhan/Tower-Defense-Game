#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <string>
#include <map>
#include <QPainter>
#include <QTimer>
#include "structures.h"
#include "monster.h"
#include "tower.h"
#include <QLabel>
#include "player.h"
using namespace  std;

#define mapBlockLen 70



namespace Ui {
class GameWindow;
}

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    GameWindow(string path);//初始化函数，传进来地图txt的路径


private:
    Ui::GameWindow *ui;


    int basic_map[8][13];
    map<int,string> Pics={     //记录地图不同点上需填充的图像 //图片太大了！！需要找小一点的图片
            {0,":/image/grass1.jpg"},  //起点
            {1,":/image/grass1.jpg"},  //路/近战塔坑
            {2,":/image/water.jpg"},  //非路且靠近路/远程塔坑
            {3,":/image/sand.jpg"},  //啥也不是
            {4,":/image/grass1.jpg"}   //终点
        };

    int MonsterNumber;
    vector<Monster> Monsters;//怪兽们
    vector<Tower> Towers;//防御塔们
    vector<vector<Pos>> MonsterWays;//Monster的所有可能路线
    Player player;
    QTimer *timer_monster;//生成怪兽计时器
    QTimer* timer_game;//游戏定时器

    void loadmap(string map);
    void paintEvent(QPaintEvent*);
    void drawMap(QPainter&);
    void playMusic();
    void drawMonster(QPainter&);
public slots:
    void addMonster();
    void gaming();
};

#endif // GAMEWINDOW_H
