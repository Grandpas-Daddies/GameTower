//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_WORD_H
#define GAMETOWER_WORD_H

#include <iostream>

class Word {
public:
    Word();
private:
    std::string word;
    int length;
    char effect; // h: heal, d: damage, s: slow, f: fast
    bool is_finished;
    int position;
};

#endif //GAMETOWER_WORD_H
