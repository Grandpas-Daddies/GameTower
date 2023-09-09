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
    this->curhp=hp;
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

std::vector<std::string> readMonsterWordList(const std::string& filename, int numLines) {
    std::ifstream file("../Assets/" + filename);
    std::vector<std::string> wordList;
    std::string line;

    for (int i = 0; i < numLines; ++i) {
        if (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string word;

            while (std::getline(ss, word, ' '))
                wordList.push_back(word);
        }
        else
            break;
    }
    return wordList;
}

Monster createMonster(const std::string&filename, int hp, int damage,int numLines) {
    std::vector<std::string> wordList = readMonsterWordList(filename, numLines);
    std::vector<Word> words;
    std::ifstream file("../Assets/" + filename);

    for (const auto& word_str : wordList) {
        int length = word_str.size();
        char effect = 'd';
        Word word(length, word_str, effect);
        words.push_back(word);
    }
    std::vector<std::string> descriptions = readMonsterDes(".monsterDes");
    std::string description;
    for (const auto& desc : descriptions)
        description += desc + " ";

    return Monster(hp, damage, words, description);
}
#endif //GAMETOWER1_MONSTER_H
