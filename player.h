#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>
using namespace std;


class Player
{
public:
    Player();
    int getLife(){return life;}

private:
    int life;//生命值
    vector<int> bag;//背包，待实现



};

#endif // PLAYER_H
