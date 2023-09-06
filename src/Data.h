//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_DATA_H
#define GAMETOWER_DATA_H

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

void saveData(Player &player) {
    // create data
    std::ofstream dataFile(player.getName() + ".dat", std::ios::trunc);
    // player main attributes
    dataFile << player.getHP() << ' ' << player.getName() << endl;
    // player position
    dataFile << player.getPos().line << ' ' << player.getPos().column << endl;
    // player backpack
    dataFile << "Backpack" << endl;
    player.getBackpack().showItemList(dataFile);
    // player word list
    dataFile << "WordList" << endl;
    player.showWordList(dataFile);
    // player map
    dataFile << "Map" << endl;
    dataFile << player.getMap().getProgress() << endl;
    player.getMap().showMap(dataFile);
}

void init(Player& player) {
    if (dataExist(player.getName()))
    {
        // if data exists, ask for loading
        cout << "数据已存在，是否读取？" << endl;
        Menu menu[2]{
                "是",
                "否"
        };
        switch (switcher(menu, 2))
        {
            case 0:
                return;
            case 1:
                saveData(player);
        }
    }
    else
    {
        saveData(player);
    }
}

void loadGame(Player &player);
void loadData(Player &player)
{
    if (dataExist(player.getName()))
    {
        std::ifstream dataFile(player.getName() + ".dat");
        // player main attributes
        int hp;
        string name;
        dataFile >> hp >> name;
        player.setHP(hp);
        player.setName(name);
        // player position
        int line, column;
        dataFile >> line >> column;
        player.setPos(line, column);
        // player backpack
        string type;
        dataFile >> type;
        if (type == "Backpack")
        {
            player.getBackpack().loadItemList(dataFile);
        }
        // player word list
        dataFile >> type;
        if (type == "WordList")
        {
            player.loadWordList(dataFile);
        }
        // player map
        dataFile >> type;
        if (type == "Map")
        {
            int progress;
            dataFile >> progress;
            player.getMap().setProgress(progress);
            player.getMap().loadMap(dataFile);
        }
    }
    else
    {
        // data does not exist, create new data
        cout << "数据不存在，创建新存档" << endl;
        saveData(player);
    }
}

void newGame(Player &player) {
    system("cls");
    init(player);
    system("cls");
    loadGame(player);
    system("pause");
}

void loadGame(Player &player) {
    loadData(player);
    Map::printMap();
    onMap(player);
    saveData(player);
    goodbye();
    system("pause");
}




#endif //GAMETOWER_DATA_H
