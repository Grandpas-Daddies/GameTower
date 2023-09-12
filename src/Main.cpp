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
    PosControl::getPos(x, y);
    PosControl::setPos(x, 0);
    cout << "\33[2K";
    cout << "请输入你的名字：";
    cin >> name;
    while (name.length() > 15 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") !=
                                 string::npos) {
        PosControl::setPos(x, 0);
        // 清除当前行
        cout << "\33[2K" << endl;
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

    cout << "    你好，名为 ";
    //文字设为黄色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << name ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << " 的 Alex Potter！" << endl;
    // 不使用\33，清除当前行
    string spaceLine(100, ' ');
    cout << spaceLine << endl << spaceLine << endl;
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
