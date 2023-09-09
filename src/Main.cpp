//
// Created by Jiarong on 2023/8/21.
//

//A MUD Game

#define NOMINMAX

#include <iostream>
#include <csignal>
#include "Interface.h"
#include "Data.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;



int main() {
    //setDPI();
    welcomePage();
    int x, y;
    string name;
    cout << "请输入你的名字：";
    PosControl::getPos(x, y);
    cin >> name;
    Player player(name);
    Monster monster1 = createMonster(".wordlistDefence", 20, 1, 1);
    Monster monster2 = createMonster(".wordlistDefence", 80, 5, 2);
    Monster monster3 = createMonster(".wordlistDefence", 120, 10, 3);
    Monster monster4 = createMonster(".wordlistDefence", 190, 20, 4);
    Monster monster5 = createMonster(".wordlistDefence", 320, 30, 5);
    PosControl::setPos(x, 0);
    cout << "    你好，名为\033[5m " << name << " \033[0m的 Alex Potter！" << endl << endl;
    Menu menu[3]{
            "新游戏",
            "加载游戏",
            "退出游戏"
    };
    switch (switcher(menu, 3)) {
        case 0:
            newGame(player);
            break;
        case 1:
            loadGame(player);
            break;
        case 2:
            goodbye();
            return 0;
    }
    return 0;
}
