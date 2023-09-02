//
// Created by Jiarong on 2023/8/21.
//

//A MUD Game

#define NOMINMAX

#include <iostream>
#include <csignal>
#include "Interface.h"
#include "Init.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;



int main() {
    //setDPI();
    welcomePage();
    Player player;
    Map map;
    switch (switcher()) {
        case 0:
            newGame(player, map);
            break;
        case 1:
            loadGame(player, map);
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
