//
// Created by hang on 2023-08-22.
//

#ifndef GAMETOWER1_MONSTER_H
#define GAMETOWER1_MONSTER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include "Creature.h"
#include "Word.h"

class Monster : public Creature {
public:
    Monster() = default;
    Monster(int monsterNumber);
    Monster(int HP, int damage, std::vector<Word> wordList, const std::string description);
    std::vector<Word>& deliverWord() { return this->wordList; } const
    int getHP() { return hp; }
    std::string des() { return this->description; }
    void readMonsterData(int monsterNumber);
    ~Monster() = default;
//    Monster operator=(const Monster& monster) {
//        this->hp = monster.hp;
//        this->damage = monster.damage;
//        this->wordList = monster.wordList;
//        this->description = monster.description;
//        return *this;
//    }
private:
    int damage;
    std::vector<Word> wordList;
    std::string description;
};

Monster::Monster(int monsterNumber) {
    this->readMonsterData(monsterNumber);
}

void Monster::readMonsterData(int monsterNumber) {
    std::string numberString = std::to_string(monsterNumber);
    std::string filePath = "./Assets/.Monster" + numberString;
    std::ifstream file(filePath);
    std::string word;
    wordList.clear();
    file >> hp;
    file >> damage;
    currHP = hp;
    std::getline(file >> std::ws, description);

    while (file >> word)
        wordList.push_back(Word(word.size(), word, 'd'));

}

#endif //GAMETOWER1_MONSTER_H
