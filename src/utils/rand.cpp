//
// Created by BiDuang on 2023/8/28.
//

#include "rand.h"

int randInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}