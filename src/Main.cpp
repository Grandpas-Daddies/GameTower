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
    while (name.length() > 15 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") !=
                                 string::npos) {
        PosControl::setPos(x, 0);
        // 清除当前行
        cout << "\033[2K";
        // 根据Windows文件名允许用的字符，判断name是否合法
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") !=
            string::npos) {
            cout << "名字中含有非法字符，请重新输入：";
        } else {
            cout << "名字过长，请重新输入：";
        }
        cin >> name;
    }
    PosControl::setPos(x, 0);
    Player player(name);

    // TODO:
    cout << "    你好，名为\033[5m " << name << " \033[0m的 Alex Potter！" << endl << "\033[2K" << endl << "\033[2K";
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
            system("pause");
            return 0;
    }
    return 0;
}
