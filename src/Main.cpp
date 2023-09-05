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
    PosControl::setPos(x, 0);
    cout << "    你好，名为\033[5m " << name << " \033[0m的 Alex Potter！" << endl << endl;
    switch (switcher()) {
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
    system("cls");
    system("pause");
/*
    atexit([]() {
        system("cls");
        ifstream dpiFile("currDPI.txt");
        string dpi;
        dpiFile >> dpi;
        dpiFile.close();
        string command = "SetDpi.exe " + dpi;
        system(command.c_str());
        remove("currDPI.txt");
    });*/

    return 0;
}
