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

bool dataExist(const string &name) {
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

void init(Player &player) {
    if (dataExist(player.getName())) {
        // if data exists, ask for loading
        cout << "数据已存在，是否读取？" << endl;
        Menu menu[2]{
                "是",
                "否"
        };
        switch (switcher(menu, 2)) {
            case 0:
                return;
            case 1:
                saveData(player);
                player.getBackpack().progress0();
                player.playerWordlist(player.getMap().getProgress() + 1);
        }
    } else {
        saveData(player);
        player.getBackpack().progress0();
        player.playerWordlist(player.getMap().getProgress() + 1);
    }
}

void loadGame(Player &player);

void loadData(Player &player) {
    if (dataExist(player.getName())) {
        std::ifstream dataFile(player.getName() + ".dat");
        // player main attributes
        int hp;
        string name;
        dataFile >> hp >> name;
        player.setHP(hp);
        player.resetCurrHP();
        player.setName(name);
        // player position
        int line, column;
        dataFile >> line >> column;
        player.setPos(line, column);
        // player backpack
        string type;
        dataFile >> type;
        if (type == "Backpack") {
            string itemName;
            while (dataFile >> itemName) {
                if (itemName == "#") {
                    break;
                }
                int effect, cooldown, num;
                dataFile >> effect >> cooldown >> num;
                player.getBackpack().loadItemList(itemName, effect, cooldown, num);
            }
        }
        dataFile.clear();
        dataFile >> type;
        if (type == "WordList") {
            int length;
            std::string word;
            int effect;
            while (dataFile >> length) {
                if (length == 0) {
                    break;
                }
                dataFile >> word >> effect;
                player.loadWordList(length, word, effect);
            }
        }
        dataFile.clear();
        dataFile >> type;
        if (type == "Map") {
            int progress;
            dataFile >> progress;
            player.getMap().setProgress(progress);
            player.getMap().loadMap(dataFile);
        }
    } else {
        system("cls");
        cout << "数据不存在，创建新存档" << endl;
        saveData(player);
        system("pause");
    }
}

void newGame(Player &player) {
    system("cls");
    init(player);
    system("cls");
    loadGame(player);
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
