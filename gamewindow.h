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
using namespace  std;

#define mapBlockLen 80



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
        {0,":/image/path3.jpg"},  //起点
        {1,":/image/path3.jpg"},  //路/近战塔坑
        {2,":/image/path4.jpg"},  //非路且靠近路/远程塔坑
        {3,":/image/stone4.jpg"},  //啥也不是
        {4,":/image/dest1.jpg"}   //终点
    };

    vector<Monster> Monsters;//怪兽们
    vector<Tower> Towers;//防御塔们
    vector<vector<Pos>> MonsterWays;//Monster的所有可能路线
    int MonsterNumber;//怪兽数量
    QTimer *timer_monster;//生成怪兽计时器
    QTimer* timer_game;//游戏定时器

    SelectionFrame selectionFrame;      //选择框类
    void loadMap(string path);//初始化地图


    void paintEvent(QPaintEvent*);
    void drawMap(QPainter&);
    void drawSelectionFrame(QPainter& painter)；


public slots:
    void addMonster();
    void refreshGameWindow();

};

#endif // GAMEWINDOW_H
