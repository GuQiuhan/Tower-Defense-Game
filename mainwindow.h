#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include "gamecontroller.h"
#include "customscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int i=1,QWidget *parent = nullptr);
    ~MainWindow();
    void setVersion(int i);
    int getVersion(){return version;}

private:
    Ui::MainWindow *ui;
    //QGraphicsScene *scene;
    CustomScene* scene;
    //QGraphicsProxyWidget *labelProxy;//背景widget的代理
    GameController* gamecontroller;
    void InitBackground();
    void InitListWidget();
    void InitPositions();
    void test();//用来调试地图路径坐标

    void createActions();
    void createMenus();

    QAction *newGameAction;
    QAction *pauseAction;
    QAction *resumeAction;
    QAction *exitAction;
    QAction *gameHelpAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    int version;
    int basic_map[8][13];//存储地图，*70像素



private slots:
    //void adjustViewSize();
    void newGame();
    void gameHelp();
    void about();
    void updateText();
    void updateBonus();

};


#endif // MAINWINDOW_H
