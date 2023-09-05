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
    void setNextPlaceUnlock(int line, int column);
private:
    Location *locations[10][10]{};
};

Map::Map() {

    for (int i = 0; i <= 9; i++)
        for (int j = 0; j <= 9; j++)
            locations[i][j] = new Location();

    locations[8][4] = new Place("校门", 34, 50, 6, 4, false);
    locations[7][4] = new Road(true);
    locations[6][4] = new Place("迎新大厅", 26, 50, 4, 4);
    locations[5][4] = new Road(true);
    locations[4][4] = new Place("庆功宴会厅", 18, 50, 4, 2);
    locations[3][4] = new Road(true);
    locations[2][4] = new Place("圣坛", 8, 52, 8, 4);
    locations[4][2] = new Place("战前准备营地",19, 13, 4, 6);
    locations[4][3] = new Road(true);
    locations[4][5] = new Road(true);
    locations[4][6] = new Place("秘密会议室", 18, 84, 2, 6);
    locations[2][5] = new Road(true);
    locations[2][6] = new Place("神秘的魔法墓地", 6, 84, 2, 4);
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
    cout << "\033[34;50H校门";
    cout << "\033[26;50H迎新大厅";
    cout << "\033[18;50H庆功宴会厅";
    cout << "\033[8;52H圣坛";
    cout << "\033[19;13H战前准备营地";
    cout << "\033[18;84H秘密会议室";
    cout << "\033[6;84H神秘的魔法墓地";
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

void Map::setNextPlaceUnlock(int line, int column) {
    int nextLine = dynamic_cast<Place*>(this->getLocation(line, column))->getNextLine();
    int nextColumn = dynamic_cast<Place*>(this->getLocation(line, column))->getNextColumn();
    dynamic_cast<Place*>(this->getLocation(nextLine, nextColumn))->setUnlock();
    cout << dynamic_cast<Place*>(this->getLocation(nextLine, nextColumn))->getIsLocked();
}

#endif //GAMETOWER_MAP_H
