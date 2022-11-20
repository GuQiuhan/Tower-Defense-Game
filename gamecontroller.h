#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H


#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
//#include "gamewindowtwo.h"


class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);
    ~GameController();


public slots:
//    void pause();
//    void resume();
//    void gameOver();
protected:
//     bool eventFilter(QObject *object, QEvent *event);

private:
//    void handleKeyPressed(QKeyEvent *event);

//    void setResume();
//    QAction * resumeAction;
      QTimer timer;
      QGraphicsScene &scene;

//    bool isPause;
};

#endif // GAMECONTROLLER_H
