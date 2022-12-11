#ifndef FINDMONSTERWAY_H
#define FINDMONSTERWAY_H

#include <vector>
#include <iostream>
#include <QDebug>
using namespace std;

#include <QPointF>
const int mapBlockLen=70;

class FindMonsterWay
{
private:
    vector<vector<QPointF>> MonsterWays;//所有路线，单位为像素
    vector<QPointF> tmp;//当前路线，单位非像素
    int map[8][13];
    int dirctions[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };//上下左右移动的距离


    int check(int x, int y)
    {
        if (x >= 0 && y >= 0 && x < 8 && y < 13 && (map[x][y] == 1||map[x][y] == 4 ))
            return 1;

        return 0;
    }

    void dfs(int i, int j)
    {
        tmp.push_back(QPointF(i,j));

        int mm=map[i][j];
        map[i][j] = -1;
        for (int k = 0; k < 4; k++)
        {
            int x = i + dirctions[k][0];
            int y = j + dirctions[k][1];

            if (check(x, y))
            {
                if (map[x][y] == 4)//终点
                {
                    tmp.push_back(QPointF(x,y ));
                    MonsterWays.push_back(tmp);
                    tmp.pop_back();

                    return;
                }
                else
                {
                   // int mm=map[i][j];
                   // map[i][j] = -1;
                    dfs(x, y);
                   // map[i][j] = mm;
                }
            }
            else continue;
        }
        map[i][j] = mm;
        tmp.pop_back();
    }


public:
    void test(int map[][13])
    {
        FindWay(map);
        for(int i=0; i<MonsterWays.size(); ++i)
        {
            qDebug()<<"begin1:";
            for(int j=0; j<MonsterWays[i].size(); ++j)
            {
                qDebug()<<MonsterWays[i][j];
            }
            qDebug()<<"end1.";
        }
    }

    vector<vector<QPointF>> FindWay(int m[][13])
    {
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<13; ++j)
            {
                map[i][j]=m[i][j];
            }

        }

        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<13; ++j)
            {
                if (map[i][j] == 0) //0起点
                {
                    tmp.clear();
                    dfs(i, j);
                }
            }

        }


        //转换为像素
        vector<vector<QPointF>> way;
        for(int i=0; i<MonsterWays.size(); ++i)
        {
            vector<QPointF> t;
            for(int j=0; j<MonsterWays[i].size(); ++j)
            {
                t.push_back(QPointF(MonsterWays[i][j].y()*mapBlockLen+0.5*mapBlockLen,MonsterWays[i][j].x()*mapBlockLen+0.5*mapBlockLen));
            }
            way.push_back(t);
        }


        return way;

    }





};

#endif // FINDMONSTERWAY_H
