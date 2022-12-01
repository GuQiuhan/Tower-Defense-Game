#include "gamestart.h"
#include "ui_gamestart.h"
#include "mainwindow.h"
#include <string>
#include <QMouseEvent>

#include<QSound>

#include <Qmovie>

#include <load.h>
#include <unistd.h>

using namespace std;

extern string path1;
extern string path2;
extern string path3;


GameStart::GameStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameStart)
{
   // ui->checkBox_1->QAbstractButton::setChecked(true);
    ui->setupUi(this);
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(":/image/start1.jpg");
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);


    ui->label_2->setScaledContents(true); //使QTlabel标签显示的图片大小都能填满label

    ui->label_2->installEventFilter(this);//给Qlabel添加clicked功能

    //playMusic();//播放
    //sound = new QSound(":/music/bgm3.wav");//内存较小，播放流畅
    //sound->play();


    //界面渲染增加gif
    QMovie *movie1 = new QMovie(":/gif/bat.gif");
    ui->label_3->setMovie(movie1);                  // 在标签中添加动画
    movie1->start();

    QMovie *movie2 = new QMovie(":/gif/frog.gif");
    ui->label_4->setMovie(movie2);                  // 在标签中添加动画
    movie2->start();

    QMovie *movie3 = new QMovie(":/gif/skeleton.gif");
    ui->label_5->setMovie(movie3);                  // 在标签中添加动画
    movie3->start();


}

GameStart::~GameStart()
{
    delete ui;
}


void GameStart::loading()
{
    this->close();
    Load l;
    l.exec();
    //q=new QTimer();
    //connect(q,SIGNAL(timeout()),this,SLOT(start()));
    //q->start(2000);
    //sleep(4);
    start();
}

void GameStart::start()
{
    //cout<<"here"<<endl;
    //l.close();
    //sound->stop();//停止音乐
    delete sound;//及时删除防止内存泄露
    if(ui->checkBox_1->isChecked())//根据选项创建不同的地图
    {
        this->accept();
    }
    else if(ui->checkBox_2->isChecked())//可自定义地图关卡
    {
        //GameWindow w(path1);
        //w.exec();
    }

}

bool GameStart::eventFilter(QObject* watched, QEvent* event)
{
    //判断对象是否为label_2
    if (watched == ui->label_2)
    {
        //判断事件类型是否为鼠标事件
        if (event->type() == QEvent::MouseButtonPress)
        {
            //转换为鼠标事件
            QMouseEvent* mouseenevt = static_cast<QMouseEvent*>(event);
            //判断鼠标左键点击
            if (mouseenevt->button() == Qt::LeftButton)
            {
                ui->label_2->setStyleSheet("QLabel \
                        {\
                                border-width:2px;\
                                border-style:dotted;\
                        }");

                //loading(); //这里要进行补充！！
                start();
                return true;
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void GameStart::mousePressEvent(QMouseEvent *e)
{
    ui->label_2->setStyleSheet("QLabel \
    {\
            border-width:0px;\
            border-style:solid;\
    }");
}



