//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <iostream>
#include <vector>

class Monster {
public:
    Monster();
    void attack();
private:
    int blood;
    int damage;
    std::string name;
    std::vector<std::string> wordList;
};


#endif //GAMETOWER1_MONSTER_H
