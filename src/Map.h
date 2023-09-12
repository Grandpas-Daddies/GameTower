//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_MAP_H
#define GAMETOWER_MAP_H

#include "Interface.h"
#include <iostream>
#include <iomanip>
#include <fstream>

#include "Location.h"

using std::cout;
using std::endl;

class Map {
public:
    Map();
    ~Map() = default;
    static void printMap();
    Location *getLocation(int line, int column) const { return locations[line][column]; }
    void loadMap(std::istream &is = std::cin);
    void showMap(std::ostream &os = std::cout);
//    void setProgress(int line, int column) {
//        int formerLine = dynamic_cast<Place*>(locations[line][column])->getFormerLine();
//        int formerColumn = dynamic_cast<Place*>(locations[line][column])->getFormerColumn();
//        if (dynamic_cast<Place*>(locations[formerLine][formerColumn])->getHasDone()) {
//            dynamic_cast<Place*>(locations[line][column])->setIsLocked(false);
//        }
//    }
    void setHasDone(int line, int column) {
        dynamic_cast<Place*>(locations[line][column])->setHasDone(true);
        if (line == 4 && column == 2);
        if (line == 2 && column == 4) dynamic_cast<Place*>(locations[4][4])->setHasDone(true);
        setProgress(currProgress + 1);
    }
    void setProgress(int progress);
    int getProgress() const { return currProgress; }
    string getDefaultMsgDir() const { return currDefaultMsgDir; }
private:
    Location *locations[10][10]{};
    int currProgress = 0;
    string currDefaultMsgDir = "./Assets/Scene/Other/����ǰ.txt";
};

Map::Map() {

    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
            locations[i][j] = new Location();

    locations[8][4] = new Place("У��", 34, 50, false);
    locations[7][4] = new Road(true);
    locations[6][4] = new Place("ӭ�´���", 26, 50);
    locations[5][4] = new Road(true);
    locations[4][4] = new Place("�칦�����", 18, 50);
    locations[3][6] = new Road(true);
    locations[2][4] = new Place("ʥ̳", 8, 52);
    locations[4][2] = new Place("սǰ׼��Ӫ��", 19, 13);
    locations[4][3] = new Road(true);
    locations[4][5] = new Road(true);
    locations[4][6] = new Place("���ܻ�����", 18, 84);
    locations[2][5] = new Road(true);
    locations[2][6] = new Place("���ص�ħ��Ĺ��", 6, 84);
}

void Map::printMap(){
    system("cls");
    PosControl::setPos(0, 0);
    std::ifstream mapFile("./Assets/.map");
    char map;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    while (mapFile.get(map)) {
        cout << map;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    mapFile.close();

    //dyed the roads with grey
    PosControl::setPos(0, 0);
    std::ifstream pathFile("./Assets/.map_path");
    char path;
    while (pathFile.get(path)) {
        if (path != ' ') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            cout << path;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        } else if (path == '\n') {
            cout << endl;
        } else {
            cout << "\033[1C";
        }
    }
    pathFile.close();

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\033[34;50HУ��";
    cout << "\033[26;50Hӭ�´���";
    cout << "\033[18;50H�칦�����";
    cout << "\033[8;52Hʥ̳";
    cout << "\033[19;13Hսǰ׼��Ӫ��";
    cout << "\033[18;84H���ܻ�����";
    cout << "\033[6;84H���ص�ħ��Ĺ��";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    PosControl::setPos(0, 0);
}

void Map::loadMap(std::istream &is) {
    int line, column;
    bool hasDone, isLocked;
    while (is >> line >> column >> hasDone >> isLocked) {
        dynamic_cast<Place*>(locations[line][column])->setHasDone(hasDone);
        dynamic_cast<Place*>(locations[line][column])->setIsLocked(isLocked);
    }
}

void Map::showMap(std::ostream &os) {
    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
        {
            if (locations[i][j]->isPlace())
            {
                Place *place = dynamic_cast<Place*>(locations[i][j]);
                os << i << " " << j << " " << place->getHasDone() << " " << place->getIsLocked() << endl;
            }
        }

}

void Map::setProgress(int progress) {
    currProgress = std::min(5,progress);
    // set the progress (unlock the places)
    switch (progress) { // ������ã��������½���ʱ��ǰ��ĳ���Ҳ�ܽ���
        case 4:

            dynamic_cast<Place*>(locations[4][2])->setIsLocked(false);
            dynamic_cast<Place*>(locations[2][6])->setHasDone(true);
            dynamic_cast<Place*>(locations[4][4])->setIsLocked(true);
            dynamic_cast<Place*>(locations[4][4])->setHasDone(true);
        case 3:
//            dynamic_cast<Road*>(locations[4][5])->setIsAccessible(true);
            dynamic_cast<Place*>(locations[2][6])->setIsLocked(false);
            dynamic_cast<Place*>(locations[4][4])->setHasDone(false);
            dynamic_cast<Place*>(locations[4][6])->setHasDone(true);
        case 2:
//            dynamic_cast<Road*>(locations[4][5])->setIsAccessible(false);
            dynamic_cast<Place*>(locations[4][4])->setIsLocked(false);
            dynamic_cast<Place*>(locations[4][6])->setIsLocked(false);
            dynamic_cast<Place*>(locations[6][4])->setHasDone(true);
        case 1:
            dynamic_cast<Place*>(locations[6][4])->setIsLocked(false);
            dynamic_cast<Place*>(locations[8][4])->setHasDone(true);
//            dynamic_cast<Road*>(locations[7][4])->setIsAccessible(true);
        case 0:
//            dynamic_cast<Road*>(locations[7][4])->setIsAccessible(false);
            dynamic_cast<Place*>(locations[8][4])->setIsLocked(false);

    }
    // set the default message directory, using "break"
    switch (progress) {
        case 0:
            currDefaultMsgDir = "./Assets/Scene/Other/����ǰ.txt";
            break;
        case 1:
            currDefaultMsgDir = "./Assets/Scene/Other/��ӭ�´���ǰ.txt";
            break;
        case 2:
            currDefaultMsgDir = "./Assets/Scene/Other/̽��ǰ.txt";
            break;
        case 3:
            currDefaultMsgDir = "./Assets/Scene/Other/ս����־.txt";
            break;
        case 4:
        case 5:
            currDefaultMsgDir = "";
            break;
    }
}

#endif //GAMETOWER_MAP_H
