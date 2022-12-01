#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <QObject>
#include <QTimer>
#include <QAction>
#include <QGraphicsScene>
#include <vector>
#include "monster.h"
using namespace std;



class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();
    QAction *getResmueAction(){ return resumeAction;}
    void setResumeAction(QAction* r){ resumeAction = r; }

public slots:
    void pause();//暂停
    void resume();//继续
    void gameOver();
    void addMonster();
protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
     void handleKeyPressed(QKeyEvent *event);

      void setResume();
      QAction * resumeAction;
      QTimer timer;
      QGraphicsScene &scene;
      QTimer Monstertimer;//用于生产monster

      bool isPause;
      vector<Monster*> monsters;//界面中的所有monster


};

#endif // GAMECONTROLLER_H
