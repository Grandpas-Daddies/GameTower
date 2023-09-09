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
    cout << "������������֣�";
    PosControl::getPos(x, y);
    cin >> name;
    Player player(name);
    PosControl::setPos(x, 0);
    cout << "    ��ã���Ϊ\033[5m " << name << " \033[0m�� Alex Potter��" << endl << endl;
    Menu menu[3]{
            "����Ϸ",
            "������Ϸ",
            "�˳���Ϸ"
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
