//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <iostream>
#include <vector>
#include "Creature.h"

class Monster : public Creature {
public:
    Monster() = default;
    void attack();
private:
    int damage;
    std::vector<std::string> wordList;
};


#endif //GAMETOWER1_MONSTER_H
