#ifndef MONSTER_H
#define MONSTER_H
#include "structures.h"
#include <vector>
#include <string>
#include <iostream>
#define mapBlockLen 70
using namespace std;

class Monster//怪兽基类
{
private:
    vector<Pos> path; //怪兽的路线
    int life;//每种怪兽的生命值不一样
    int harm;//每种怪兽的伤害值不一样
    static constexpr int speed = 5;     //每次循环敌人移动的像素数量
    int width, height;  //宽高
    string pic;
    Pos tmp;

public:
    Monster(vector<Pos> p)
    {
        for(size_t i=0; i<p.size(); ++i)//将数组坐标转变为像素坐标
        {
            Pos t(p[i].x*mapBlockLen,p[i].y*mapBlockLen);
            path.push_back(t);
        }
        width=126;
        height=126;
        pic=":/image/monster1.gif";
        tmp.x=path[0].x;//初始化坐标
        tmp.y=path[0].y;
        path.erase(path.begin());

    }

    Monster(){}

    //怪物移动函数
    bool move()
    {
        //cout<<path[0].x<<" "<<path[0].y<<" "<<tmp.x<<" " << tmp.y<<" " <<endl;

        if(path.empty())
        {   cout<<"empty"<<endl;
            return true;
        }

        else if (path[0].y > tmp.y) //下
        {

            tmp.y += speed;

        }

        else if (path[0].x < tmp.x) //左
        {

            tmp.x -= speed;

        }

        else if (path[0].x > tmp.x) //右
        {

            tmp.x += speed;

        }

        else if (path[0].y < tmp.y) //上
        {

            tmp.y -= speed;

        }

        //如果怪物的坐标和路径点坐标重合，则删除这个路径点
        if (tmp.y == path[0].y && tmp.x == path[0].x)
        {

            path.erase(path.begin());       //删除第一个路径点

        }

    }

    Pos& getPos()
    {
        return tmp;
    }

    string getPic()
    {
        return pic;
    }

    int getWidth()
    {
        return width;
    }

    int getHeight()
    {
        return height;
    }

    void setPic(string p)
    {
        pic=p;
    }


};

class basic_Monster:public Monster //初级怪兽
{
private:

public:
    basic_Monster(vector<Pos> p)
        :Monster(p)
    {
        setPic(":/image/monster2.gif");
    }

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
