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
#include "Map.h"

class Player : public Creature {
public:
    Player();
    void Attack();
    void printMap() const;
private:
    std::vector<Word> wordList;
    Backpack backpack;
    Map map;
};

Player::Player(): map(), Creature(100, "Alex"){}

void Player::printMap() const {
    map.printMap();
}


#endif //GAMETOWER1_HERO_H
