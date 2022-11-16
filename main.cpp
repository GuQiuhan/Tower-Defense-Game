#include <QApplication>
#include <string>
#include "gamestart.h"
using namespace  std;
string path1="/Users/pro/Desktop/proj2/map1.txt";
string path2="/Users/pro/Desktop/proj2/map2.txt";
string path3="/Users/pro/Desktop/proj2/map3.txt";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameStart s;

    s.exec();


    return a.exec();
}
