#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H


#include <QGraphicsScene>
#include "gamecontroller.h"

//自定义场景类，重写了DnD 函数
class CustomScene : public QGraphicsScene
{
public:
    CustomScene(QWidget* parent);
    void setController(GameController* g){gamecontroller=g;}

protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *) Q_DECL_OVERRIDE;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *) Q_DECL_OVERRIDE;

    void dropEvent(QGraphicsSceneDragDropEvent *) Q_DECL_OVERRIDE;


private:
    GameController* gamecontroller;
};

#endif // CUSTOMSCENE_H
