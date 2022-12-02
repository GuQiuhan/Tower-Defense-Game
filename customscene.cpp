#include "customscene.h"
#include <QGraphicsSceneDragDropEvent>
#include <QMimeData>
#include <QListWidget>
#include <QGraphicsPixmapItem>
#include <QDebug>

CustomScene::CustomScene(QWidget* parent)
    :QGraphicsScene(parent)
{

}

void CustomScene::dragEnterEvent(QGraphicsSceneDragDropEvent *)
{
    //qDebug() << __FUNCTION__;
}

void CustomScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *)
{
    //qDebug() << __FUNCTION__;
}

void CustomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *pEvent)
{
    //qDebug() << __FUNCTION__;

}

void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *pEvent)
{
    //qDebug() << __FUNCTION__;

    if (pEvent->mimeData()->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QListWidget *pListwidget = qobject_cast<QListWidget *>(pEvent->source());

        //QString path= ":/image/";
        QPointF pos=pEvent->scenePos();//获取鼠标位置
        gamecontroller->addTower(pListwidget->currentItem()->text(),pos);

//        if(pListwidget->currentItem()->text()=="MoonTower")
//        {
//            path+= "MoonTower.jpg";//构造路径

//        }
//        else if(pListwidget->currentItem()->text()=="GunTower1") path+= "tower4_v1.jpg";
//        else if(pListwidget->currentItem()->text()=="GunTower2") path+= "tower5_v1.jpg";
//        else if(pListwidget->currentItem()->text()=="GunTower3") path+= "tower4_v2.jpg";
//        else if(pListwidget->currentItem()->text()=="GunTower4") path+= "tower5_v2.jpg";

//        QGraphicsPixmapItem *pPixmapItem = new QGraphicsPixmapItem(QPixmap(path));

//        pPixmapItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
//        pPixmapItem->setPos(pEvent->scenePos());

//        addItem(pPixmapItem);
    }
}
