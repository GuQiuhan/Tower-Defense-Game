#include "load.h"
#include "ui_load.h"
#include <QMovie>

Load::Load(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Load)
{
    ui->setupUi(this);
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/image/start1.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);

    QMovie *movie1 = new QMovie(":/gif/Dino1.gif");
    ui->label->setMovie(movie1);                  // 在标签中添加动画
    ui->label->setScaledContents(true);
    movie1->start();

    QMovie *movie2 = new QMovie(":/gif/Dino2.gif");
    ui->label_2->setMovie(movie2);                  // 在标签中添加动画
   ui->label_2->setScaledContents(true);
    movie2->start();

    QMovie *movie3 = new QMovie(":/gif/Dino3.gif");
    ui->label_3->setMovie(movie3);                  // 在标签中添加动画
    ui->label_3->setScaledContents(true);
    movie3->start();



}

Load::~Load()
{
    delete ui;
}
