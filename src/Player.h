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
#include "Interface.h"

struct MapPosition {
    int line;
    int column;
};
//player 伤害结算用word.getEffect() 里读出来的数字
class Player : public Creature {
public:
    Player() = default;
    explicit Player(string name);
    void printStatus() const;
    MapPosition& getPos() { return pos; }
    MapPosition& getLastPos() { return lastPos; }
    std::vector<Word> deliverWord() { return this->wordList; }
    int getHP() {return hp;}
    Map& getMap() { return map; }
    Backpack& getBackpack() { return backpack; }
    void setPos(int line, int column) { pos.line = line; pos.column = column; }
    void playerWordlist(int playerNumber); //读取玩家攻击词
    void showWordList(std::ostream &os = std::cout) const {
        for (Word word : wordList) {
            os << word.getLength() << word.getName() << " " << word.getEffect() << std::endl;
        }
        os << "0" << std::endl;
    }

    void loadWordList(std::istream &is = std::cin) {
        int length;
        std::string name;
        char effect;
        while (is >> length) {
            if (length == 0) {
                return;
            }
            is >> name >> effect;
            Word word(length, name, effect);
            wordList.push_back(word);
        }
    }
private:
    int damage = 1; //应该用不到这个东西。玩家伤害结算都靠每个word的wordDamage
    Map map;
    std::vector<Word> wordList;
    Backpack backpack;
    MapPosition pos = {8, 4};
    MapPosition lastPos = {8, 4};
};

Player::Player(string name): Creature(100, name){ currHP = hp; }

void Player::printStatus() const {
    PosControl::setPos(0,0);
    cout << "\33[47;33m" << "Alex Potter" << "\33[0m" << endl;
    cout << endl;
    cout << "\33[47;33m" << "HP: " << "\33[0m" << hp << endl;
    cout << "\33[47;33m" << "Backpack: " << "\33[0m" << endl;
    backpack.showItemList();
    cout << "\33[47;33m" << "WordList: " << "\33[0m" << endl;
    showWordList();
    cout << endl;
    cout << "按 \33[31m[Q] \33[0m退出游戏" << endl;
    cout << "按 \33[31m[W][A][S][D] \33[0m或 \33[31m[↑][←][↓][→] \33[0m移动" << endl;
    cout << "按 \33[31m[F5] \33[0m刷新地图" << endl;
}

void Player::playerWordlist(int playerNumber) {
    int wordDamage[6] = {0, 1, 3, 5, 10, 20};
    std::string numberString = std::to_string(playerNumber);
    std::string filePath = "./Assets/.wordlistAttack";
    std::ifstream file(filePath);
    std::string line;

    int lineNumber = 1;
    while (std::getline(file, line)) {
        if (lineNumber == playerNumber) {
            std::istringstream iss(line);
            std::string word;
            while (iss >> word) {
                wordList.push_back(Word(word.size(), word, wordDamage[playerNumber]));
            }
            break;
        }
        lineNumber++;
    }
}


#endif //GAMETOWER1_HERO_H
