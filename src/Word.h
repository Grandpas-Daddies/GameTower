//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_WORD_H
#define GAMETOWER_WORD_H

#include <iostream>

class Word {
public:
    Word();
    Word(int length,std::string word,char effect);
    void putWord();
    void changeColor(int pos,int co);

    int getLength(){ return length; }
    std::string getString(){ return word; }
    void changeState(bool state);
    bool getState(){ return isFinished; }
    int getCur() { return cur; }
    void changeCur(int cur){ this->cur=cur; }
private:
    std::string word;
    int length;
    char effect; // h: heal, d: damage, s: slow, f: fast
    bool isFinished;
    int position;
    std::vector<int> color;
    int cur; //

};

Word::Word() {
    isFinished=false;
}

void Word::changeState(bool state) {
    isFinished=state;
}

void Word::putWord() {

    for(int i=0;i<position;i++)cout<<' ';
    if(isFinished) {
        for(int i=0;i<length;i++){
            cout<<' ';
        }
        return;
    }
    for(int i=0;i<length;i++){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color[i]);
        cout<<word[i];
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);

}

void Word::changeColor(int pos, int co) {
    color[pos]=co;
}

Word::Word(int length,std::string word,char effect) {
    isFinished=false;
    this->length=length;
    this->effect=effect;
    this->word=word;
    position=rand()%101;
    cur=0;
    isFinished=0;
    for(int i=0;i<length;i++){
        color.push_back(8);
    }
}

#endif //GAMETOWER_WORD_H
