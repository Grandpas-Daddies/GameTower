//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <iostream>
#include <vector>
#include "Creature.h"
#include "Word.h"

class Monster : public Creature {
public:
    Monster() = default;
    Monster(int HP,int damage,std::vector<Word> wordList);
    void attack();
    std::vector<Word> deliverWord() { return this->wordList; }
    int getHP(){ return hp;}
private:
    int damage;
    std::vector<Word> wordList;
};

Monster::Monster(int HP,int damage,std::vector<Word> wordList) {
    this->damage=damage;
    this->wordList=wordList;
    this->hp=HP;
}

#endif //GAMETOWER1_MONSTER_H
