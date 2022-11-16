#ifndef TOWER_H
#define TOWER_H
#include "monster.h"
#include <vector>
using namespace std;


class Tower
{
public:
    Tower();
    bool inRange(Monster& m);//判断是否在范围内
    void Attack(vector<Monster>& monsters);//攻击在范围内的怪兽
};

#endif // TOWER_H
