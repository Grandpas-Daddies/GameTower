//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_CREATURE_H
#define GAMETOWER_CREATURE_H

#include <string>

class Creature {
public:
    Creature();
    void getName() const;

protected:
    int blood;
    std::string name;
};

#endif //GAMETOWER_CREATURE_H
