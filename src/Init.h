//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_INIT_H
#define GAMETOWER_INIT_H

#include <iostream>
#include <fstream>
#include "Map.h"
#include "Player.h"
#include "Behavior.h"

bool dataExist(const string& name) {
    string fileName = name + ".dat";
    std::ifstream dataFile(fileName);
    bool isOpen = dataFile.is_open();
    dataFile.close();
    return isOpen;
}

void init(Player& player) {
    string name;
    cout << "ÇëÊäÈëÄãµÄÃû×Ö£º";
    cin >> name;
    if (dataExist(name))
    {
        // if data exists, ask for loading
    }
    else
    {
        // create data
        std::ofstream dataFile(name + ".dat");
        // player main attributes
        dataFile << player.getHP() << ' ' << player.getName() << endl;
        // player position
        dataFile << player.getPos().line << ' ' << player.getPos().column << endl;
        // player backpack
        dataFile << "B" << endl;
        player.getBackpack().showItemList(dataFile);
        // player word list
        dataFile << "W" << endl;
        player.showWordList(dataFile);
        // player map
        dataFile << "M" << endl;
        dataFile << 0 << endl;
    }
}

void loadGame(Player &player);
void newGame(Player &player) {
    init(player);
    system("cls");
    loadGame(player);
    system("pause");
}

void loadGame(Player &player) {
    loadData(player);
    Map::printMap();
    onMap(player);
    goodbye();
    system("pause");
}




#endif //GAMETOWER_INIT_H
