#include <QApplication>
#include <string>
#include "gamestart.h"
#include "mainwindow.h"
#include <QDialog>
#include <iostream>


using namespace  std;
string path1="/Users/pro/Desktop/proj2/map1.txt";
string path2="/Users/pro/Desktop/proj2/map2.txt";
string path3="/Users/pro/Desktop/proj2/map3.txt";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameStart s;

   // MainWindow mw;//一定要定义在外面！（虽然我也不知道为什么这里定义在里面行不通）

    if (s.exec()==QDialog::Accepted)
    {
        //cout<<"here"<<endl;
        MainWindow mw(s.getVersion());
        //cout<<s.getVersion()<<endl;
        mw.setVersion(s.getVersion());
        mw.show();
        return a.exec();
    }
    else return 0;

    //return a.exec();
}
