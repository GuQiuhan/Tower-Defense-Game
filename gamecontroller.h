#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <QObject>
#include <QTimer>
#include <QAction>
#include <QGraphicsScene>
#include <vector>
#include "monster.h"
#include "bullet.h"
#include "tower.h"
using namespace std;

class bullet;
class MoonTower;

class GameController : public QObject
{
    Q_OBJECT
public:
    vector<string> myBonus;//供MainWindow访问
    GameController(QGraphicsScene &scene, int i=1,QObject *parent = 0);
    ~GameController();
    QAction *getResmueAction(){ return resumeAction;}
    void setResumeAction(QAction* r){ resumeAction = r; }
    void deleteBullet(bullet* b);
    void deleteMonster(Monster* m);
    void deleteTower(MoonTower* t);
    void Shoot(Monster* m,QGraphicsItem* t);//怪兽打塔，1号子弹
    void Shoot(QGraphicsItem* t,Monster* m);//塔打怪兽，2号子弹
    //void Shoot(MoonTower* m,QGraphicsItem* t);//塔打怪兽，2号子弹
    void addTowerBonus(QGraphicsItem* t,string s);
    void InitPath();//初始化路径
public slots:
    void pause();//暂停
    void resume();//继续
    void gameOver();
    void addMonster();
    void addTower(QString type,QPointF pos);
    int getRound();
    int getMonsterNumber();


protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    int version;
     void handleKeyPressed(QKeyEvent *event);

      void setResume();
      QAction * resumeAction;
      QTimer timer;
      QGraphicsScene &scene;
      QTimer Monstertimer;//用于生产monster

      bool isPause;
      vector<Monster*> monsters;//界面中的所有monster。
      vector<bullet* > bullets;
      vector<MoonTower*> towers;
      //注意这里一定要是指针类型！由于Monster类里含有引用类型，不知道应该如何构造默认构造函数，所以不可以使用类作为元素
      int Round;

      vector<vector<QPointF>> MonsterPaths;
signals:
//注意！信号函数是不需要实现的，声明后调用就可以了
      void MonsterNumberChange();//i可正可负，表示增加或减少的数量，每次Monster有变化时都需要调用
      void BonusChange();


};

#endif // GAMECONTROLLER_H
