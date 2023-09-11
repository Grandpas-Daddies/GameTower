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

    Player(string name);

    void printStatus() const;

    MapPosition &getPos() { return pos; }

    MapPosition &getLastPos() { return lastPos; }

    int getHP() { return hp; }

    Map &getMap() { return map; }

    Backpack &getBackpack() { return backpack; }

    void setPos(int line, int column) {
        pos.line = line;
        pos.column = column;
    }

    void playerWordlist(int playerNumber); //读取玩家攻击词
    void showWordList(std::ostream &os = std::cout) const {
        for (Word word: wordList) {
            os << word.getLength() << " " << word.getName() << " " << word.getEffect() << std::endl;
        }
        os << "0" << std::endl;
    }

    void printWordList() const {
        int i = 1;
        for (Word word: wordList) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            cout << "[" << i << "] ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << word.getName() << endl;
            i++;
        }
        cout << endl;
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
    //应该用不到这个东西。玩家伤害结算都靠每个word的wordDamage
    Map map;
    Backpack backpack;
    MapPosition pos = {8, 4};
    MapPosition lastPos = {8, 4};
};

Player::Player(string name) : Creature(100, name) {
    currHP = hp;
    backpack.progress0();
}

void Player::printStatus() const {
    PosControl::setPos(0, 0);
    cout << "\33[47;33m" << "Alex Potter" << "\33[0m" << endl;
    cout << endl;
    cout << "\33[47;33m" << "HP: " << "\33[0m" << hp << endl;

    cout << endl;
    cout << "按 \33[31m[B] \33[0m查看背包" << endl;
    cout << "按 \33[31m[L] \33[0m查看攻击词" << endl;
    cout << "按 \33[31m[E] \33[0m查看帮助" << endl;
    cout << "按 \33[31m[N] \33[0m查看怪物说明" << endl;
    cout << "按 \33[31m[W][A][S][D] \33[0m或 \33[31m[↑][←][↓][→] \33[0m移动" << endl;
    cout << "按 \33[31m[F5] \33[0m刷新地图" << endl;
    cout << endl;
    cout << "按 \33[31m[Q] \33[0m退出游戏" << endl;

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
