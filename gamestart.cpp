#include "gamestart.h"
#include "ui_gamestart.h"
#include "gamewindow.h"
#include <string>
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
}

GameStart::~GameStart()
{
    delete ui;
}


void GameStart::on_start_clicked()
{
    if(ui->checkBox_1->isChecked())//根据选项创建不同的地图
    {
        GameWindow w(path1);
        w.exec();
    }
    else if(ui->checkBox_2->isChecked())
    {
        GameWindow w(path2);
        w.exec();
    }
    else if(ui->checkBox_3->isChecked())
    {
        GameWindow w(path3);
        w.exec();
    }
}
