//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_HERO_H
#define GAMETOWER1_HERO_H

#include "Backpack.h"
#include <iostream>
#include <vector>


class Hero {
public:
    Hero();
    void attack();
private:
    int blood;
    std::vector<std::string> wordList;
    std::string name;
    Backpack backpack;
};


#endif //GAMETOWER1_HERO_H
