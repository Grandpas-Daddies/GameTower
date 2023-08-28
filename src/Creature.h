//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_CREATURE_H
#define GAMETOWER_CREATURE_H

#include <iostream>
#include <string>

class Creature {
public:
    Creature(): hp(0), name("") {};
    Creature(int hp, std::string name): hp(hp), name(name) {};
    std::string getName() const { return name; }

protected:
    int hp; // health point
    std::string name;
};

#endif //GAMETOWER_CREATURE_H
