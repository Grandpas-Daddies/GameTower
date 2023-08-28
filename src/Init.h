//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_INIT_H
#define GAMETOWER_INIT_H

#include <iostream>
#include <fstream>
#include "../include/json.hpp"
#include "Map.h"
#include "Player.h"

using nlohmann::json;

void readData(json &data) {
    std::cout << "读取存档中..." << std::endl;
    std::cout << "读取成功！" << std::endl;
    //TODO: read data from json
}

void createData(json &data) {
    json newData;
    //TODO: create data
//    newData = json::parse(R"(
//    {
//        "name": "default",
//        "level": 1,
//        "exp": 0,
//        "hp": 100,
//        "maxHp": 100,
//        "attack": 10,
//        "defense": 10,
//        "money": 0,
//        "items": [],
//        "skills": [],
//        "location": {
//            "x": 7,
//            "y": 11
//        }
//    }
//    )");
    data.push_back(newData);
}

void init() {
//    std::ifstream profile("profile.dat");
//    json data = json::parse(profile);
//    if (!data.empty()) {
//        std::cout << "检测到存档，是否读取存档？(Y/N)" << std::endl;
//        char choice;
//        int x,y;
//        setPos(x, y);
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
//        std::cin >> choice;
//        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
//        while (1) {
//            if (choice == 'N' || choice == 'n') {
//                createData(data);
//                break;
//            } else if (choice != 'Y' && choice != 'y') {
//                std::cout << "输入错误，请重新输入！";
//                system("pause");
//                //reset the cursor position and clear the line
//                setPos(x, y);
//                std::cout << "                                                                  " << std::endl
//                          << "                                                                  ";
//            }
//            return;
//        }
//    } else {
//        createData(data);
//    }
//    readData(data);
}

void newGame(Player &player) {
    init();
    system("cls");
    player.printMap();
//    Sleep(1000);
    system("pause");
}

void loadGame(Player &player) {
//    transAnimation();
    json data;
    readData(data);
}




#endif //GAMETOWER_INIT_H
