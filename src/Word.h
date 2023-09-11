//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_WORD_H
#define GAMETOWER_WORD_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <random>

using std::cout;

class Word {
public:
    Word();

    Word(int length, std::string word, char effect);

    void putWord();

    void changeColor(int pos, int co);

    int getLength() { return length; }

    std::string getString() { return word; }

    void changeState(bool state);

    bool getState() { return isFinished; }

    int getCur() { return cur; }

    void changeCur(int cur) { this->cur = cur; }

    int getEffect() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, 15); //概率的分母

        int random_number = distr(gen);
        if (random_number == 1) {  // 概率分子
            std::uniform_int_distribution<> distr_damage(200, 600);
            int boosted_damage = distr_damage(gen);  // 生成一个 200 到 600 的随机数
            return effect * boosted_damage / 100;  // 将 effect 增加到 200% 到 600%
        }
        return effect;
    }

    std::string getName() const { return word; }

    ~Word() = default;

private:
    std::string word;
    int length;
    int effect; // h: heal, d: damage
    bool isFinished; //用于实现变色打字，表示字是否被打完
    int position; //用于实现空格位置，随机化
    std::vector<int> color; //用于实现变色打字，表示每个字母的color属性
    int cur; //用于实现变色打字，表示当前打到第几个字

};

Word::Word() {
    isFinished = false;
}

void Word::changeState(bool state) {
    isFinished = state;
}

void Word::putWord() {

    for (int i = 0; i < position; i++)std::cout << ' ';
    if (isFinished) {
        for (int i = 0; i < length; i++) {
            cout << ' ';
        }
        return;
    }
    for (int i = 0; i < length; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color[i]);
        cout << word[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

}

void Word::changeColor(int pos, int co) {
    color[pos] = co;
}

Word::Word(int length, std::string word, char effect) {
    isFinished = false;
    this->length = length;
    this->effect = effect;
    this->word = word;
    position = rand() % 101 - length - 1;
    if(position<0)position=0;
    cur = 0;
    isFinished = 0;
    for (int i = 0; i < length; i++) {
        color.push_back(8);
    }
}

#endif //GAMETOWER_WORD_H
