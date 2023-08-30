//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_HERO_H
#define GAMETOWER1_HERO_H



#include <iostream>
#include <vector>
#include <conio.h>
#include "Backpack.h"
#include "Word.h"
#include "Creature.h"
#include "Map.h"
#include "FightScene.h"

struct MapPosition {
    int line;
    int column;
};

class Player : public Creature {
public:
    Player();
    void printStatus() const;
    MapPosition& getPos() { return pos; }
    MapPosition& getLastPos() { return lastPos; }
private:
    std::vector<Word> wordList;
    Backpack backpack;
    MapPosition pos = {8, 4};
    MapPosition lastPos = {8, 4};
};

Player::Player(): Creature(100, "Alex"){}

void Player::printStatus() const {
    PosControl::setPos(0,0);
    cout << "\33[47;33m" << "Alex Potter" << "\33[0m" << endl;
    cout << endl;
    cout << "\33[47;33m" << "HP: " << "\33[0m" << hp << endl;
    cout << "\33[47;33m" << "Backpack: " << "\33[0m" << endl;
    backpack.showItemList();
    cout << endl;
    cout << "°´ \033[31m[Q] \033[0mÍË³öÓÎÏ·" << endl << endl;
}




#endif //GAMETOWER1_HERO_H
