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
    std::vector<Word> deliverWord() { return this->wordList; }
    int getHP() {return hp;}

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
    cout << "按 \33[31m[Q] \33[0m退出游戏" << endl << endl;
    cout << "按 \33[31m[W][A][S][D] \33[0m或 \33[31m[↑][←][↓][→] \33[0m移动" << endl << endl;
    cout << "按 \33[31m[F5] \33[0m刷新地图" << endl << endl;
}




#endif //GAMETOWER1_HERO_H
