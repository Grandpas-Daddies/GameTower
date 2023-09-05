//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Creature.h"
#include "Word.h"

class Monster : public Creature {
public:
    Monster() = default;
    Monster(int HP, int damage, std::vector<Word> wordList, const std::string description);
    std::vector<Word> deliverWord() { return this->wordList; }
    int getHP() { return hp; }
    std::string des() { return this->description; }
private:
    int damage;
    std::vector<Word> wordList;
    std::string description;
};

Monster::Monster(int HP, int damage, std::vector<Word> wordList, const std::string description) {
    this->damage = damage;
    this->wordList = wordList;
    this->hp = HP;
    this->description = description;
}

std::vector<std::string> readMonsterDes(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> descriptions;
    std::string line;

    while (std::getline(file, line)) {
        descriptions.push_back(line);
    }

    return descriptions;
}
#endif //GAMETOWER1_MONSTER_H
