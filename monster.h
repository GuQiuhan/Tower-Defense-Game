#ifndef MONSTER_H
#define MONSTER_H
#include "structures.h"
#include <vector>
using namespace std;

class Monster//怪兽基类
{
private:
    vector<Pos> path; //怪兽的路线
    int life;//每种怪兽的生命值不一样
    int harm;//每种怪兽的伤害值不一样

public:
    Monster(vector<Pos> p)
        :path(p)
    {}

    Monster(){}
};

class basic_Monster:public Monster //初级怪兽
{
private:

public:
    basic_Monster(vector<Pos> p)
        :Monster(p)
    {}

};


class advanced_Monster:public Monster //初级怪兽
{
private:

public:
    advanced_Monster(vector<Pos> p)
        :Monster(p)
    {}

};


class Boss:public Monster //初级怪兽
{
private:

public:
    Boss(vector<Pos> p)
        :Monster(p)
    {}

};


#endif // MONSTER_H
