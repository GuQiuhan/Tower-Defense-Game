#include "customscene.h"
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QListWidget>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QGraphicsView>

#ifndef GLOBAL
#define GLOBAL
enum GameObjectsData {
    GD_Type
};

enum GameObjectTypes {
    GO_Tower,
    GO_Monster,
    GO_Bullet,//怪兽打塔的子弹
    GO_Bullet2,//塔打怪兽的子弹
    GO_GunTower,
    GO_Rect
};

#endif

CustomScene::CustomScene(QWidget* parent)
    :QGraphicsScene(parent)
{

}

void CustomScene::dragEnterEvent(QGraphicsSceneDragDropEvent *pEvent)
{
    //qDebug() << __FUNCTION__;

}

void CustomScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
    //qDebug() << __FUNCTION__;
}

void CustomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
    //qDebug() << __FUNCTION__;

}

void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *pEvent)
{


    if (pEvent->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QListWidget *pListwidget = qobject_cast<QListWidget *>(pEvent->source());
        QPointF pos=pEvent->scenePos();//获取鼠标位置
        if(pListwidget->currentItem()->text()=="MoonTower")
        {
            //纠正位置，moontower需要在路上
            QGraphicsItem *item = itemAt(pEvent->scenePos(),QTransform());

            if(item!=nullptr&&item->type() == QGraphicsRectItem::Type)
            {
                gamecontroller->addTower(pListwidget->currentItem()->text(),pos);
                return;
            }
        }
        else if(pListwidget->currentItem()->text()=="GunTower1"||pListwidget->currentItem()->text()=="GunTower2"||pListwidget->currentItem()->text()=="GunTower3"||pListwidget->currentItem()->text()=="GunTower4")
        {
            QGraphicsItem *item = itemAt(pEvent->scenePos(),QTransform());
            if(item!=nullptr&&item->type() == QGraphicsEllipseItem::Type)
            {
                pos=(item->scenePos() +item-> boundingRect().center()+QPointF(0,-25));
                gamecontroller->addTower(pListwidget->currentItem()->text(),pos);
                return;
            }
        }
        else if(pListwidget->currentItem()->text()=="Freeze")
        {
            //纠正位置，moontower需要在路上
            QGraphicsItem *item = itemAt(pEvent->scenePos(),QTransform());
            if(item!=nullptr&&(item->data(GD_Type) == GO_Tower||item->data(GD_Type) == GO_GunTower))
            {
                gamecontroller->addTowerBonus(item,"Freeze");
                return;
            }
        }
        else if(pListwidget->currentItem()->text()=="Injure")
        {
            //纠正位置，moontower需要在路上
            QGraphicsItem *item = itemAt(pEvent->scenePos(),QTransform());

            if(item!=nullptr&&(item->data(GD_Type) == GO_Tower||item->data(GD_Type) == GO_GunTower))
            {
                gamecontroller->addTowerBonus(item,"Injure");
                return;
            }
        }
        else if(pListwidget->currentItem()->text()=="Bleed")
        {
            //纠正位置，moontower需要在路上
            QGraphicsItem *item = itemAt(pEvent->scenePos(),QTransform());

            if(item!=nullptr&&(item->data(GD_Type) == GO_Tower||item->data(GD_Type) == GO_GunTower))
            {
                gamecontroller->addTowerBonus(item,"Bleed");
                return;
            }
        }
        return;

    }
}
