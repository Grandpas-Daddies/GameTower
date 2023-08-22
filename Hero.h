//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_HERO_H
#define GAMETOWER1_HERO_H


#include <iostream>
#include <vector>
#include "Backpack.h"
#include "Word.h"
#include "Creature.h"

class Hero {
public:
    Hero();
    void attack();
private:
    std::vector<Word> wordList;
    Backpack backpack;
};


#endif //GAMETOWER1_HERO_H
