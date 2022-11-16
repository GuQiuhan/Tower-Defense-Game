#ifndef FINDMONSTERWAY_H
#define FINDMONSTERWAY_H
#include "gamestart.h"
#include "structures.h"
#include <vector>
using namespace std;
struct Pos;

class FindMonsterWay
{
private:
    vector<vector<Pos>> MonsterWays;//所有路线
    vector<Pos> tmp;//当前路线
    int dirctions[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };//上下左右移动的距离


    int check(int x, int y, int map [][13])
    {
        if (x < 0 || y < 0 || x >= 8 || y >= 13 || (map[x][y] != 1 && map[x][y] != 4))
            return 0;

        return 1;
    }

    void dfs(int i, int j, int map[][13])
    {
        tmp.push_back(Pos(i,j));

        for (int k = 0; k < 4; k++)
        {
            int x = i + dirctions[k][0];
            int y = j + dirctions[k][1];

            if (check(x, y, map))
                if (map[x][y] == 4)
                {
                    tmp.push_back(Pos(x,y ));
                    MonsterWays.push_back(tmp);
                    return;
                }
                else
                {
                    map[i][j] = -1;
                    dfs(x, y, map);
                    map[i][j] = 1;
                }
        }

        tmp.pop_back();
    }


public:
    vector<vector<Pos>> FindWay(int map[][13])
    {
        for(int i=0; i<8; ++i)
        {
            for(int j=0; j<13; ++j)
                if (map[i][j] == 0) //0起点
                {
                    tmp.clear();
                    dfs(i, j, map);
                }
        }
        return MonsterWays;
    }





};

#endif // FINDMONSTERWAY_H
