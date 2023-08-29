//
// Created by Jiarong on 2023/8/21.
//

//A MUD Game

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <iostream>
#include "Interface.h"
#include "Init.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;

int main() {
    welcome();
    Player player;

    switch (switcher()) {
        case 0:
            newGame(player);
            break;
        case 1:
            loadGame(player);
            break;
        case 2:
            return 0;
    }
    system("cls");
    system("pause");
    return 0;
}
