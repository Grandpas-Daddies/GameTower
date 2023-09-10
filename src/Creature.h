//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_CREATURE_H
#define GAMETOWER_CREATURE_H

#include <iostream>
#include <string>
#include "Map.h"

class Creature {
public:
    Creature(): hp(0), name("") {};
    Creature(int hp, std::string name): hp(hp), name(name) {};
    void setHP(const int& hp) { this->hp = hp; }
    int getHP() const { return hp; }
    void setName(const std::string& name) { this->name = name; }
    std::string getName() const { return name; }
    void getDamaged(int damage){ currHP-=damage; };
    int getCurrHP(){ return currHP; }
    void resetCurrHP(){ currHP = hp; }
protected:
    int hp; // health point
    std::string name;
    int currHP;
};

#endif //GAMETOWER_CREATURE_H
