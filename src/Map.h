//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_MAP_H
#define GAMETOWER_MAP_H

#include "Location.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

class Map {
public:
    Map();

    void printPlainMap() const;
    void printMap() const;
private:
    Location *locations[15][15];
};

Map::Map() {

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            locations[i][j] = new Location(i, j);
        }
    }

    locations[7][11] = new Place("³Ç±¤", 7, 11);
    locations[7][10] = new Road(true, 7, 12);
    locations[7][9] = new Place("ÐÛ·åÉ½", 7, 9);
    locations[7][7] = new Place("Ó¢ÐÛ·åÉ½½Å", 7, 7);
    locations[7][6] = new Road(true, 7, 6);
    locations[7][5] = new Place("Ó¢ÐÛ·åÉ½Ñü", 7, 5);
    locations[7][4] = new Road(true, 7, 4);
    locations[7][3] = new Place("Ó¢ÐÛ·å¶¥", 7, 3);
    locations[6][9] = new Road(false, 6, 9);
    locations[6][7] = new Road(false, 6, 7);
    locations[6][5] = new Road(false, 6, 5);
    locations[5][9] = new Place("ÌìÏÕ·å", 5, 9);
    locations[5][8] = new Road(true, 5, 8);
    locations[5][7] = new Place("ÓÄ¹ÈÁÖ", 5, 7);
    locations[5][6] = new Road(true, 5, 6);
    locations[5][5] = new Place("ÌÒ»¨ÁÖ", 5, 5);
    locations[5][4] = new Road(true, 5, 4);
    locations[5][3] = new Place("ÌÒ»¨Ô´", 5, 3);
    locations[5][2] = new Road(true, 5, 2);
    locations[5][1] = new Place("Æ«Ô¶´å×¯", 5, 1);
    locations[4][7] = new Road(false, 4, 7);
    locations[3][7] = new Place("ºÚÉ­ÁÖ", 3, 7);
    locations[2][7] = new Road(true, 2, 7);
    locations[1][7] = new Place("ºÚÉ­ÁÖÃÔÎí", 1, 7);
    locations[3][8] = new Road(true, 3, 8);
    locations[3][9] = new Place("ºÚÉ­ÁÖÃÔÎí", 3, 9);
    locations[2][9] = new Road(false, 2, 9);
    locations[1][9] = new Place("ºÚÉ­ÁÖÉî´¦", 1, 9);
    locations[8][9] = new Road(true, 8, 9);
    locations[9][9] = new Place("Ð¡°«É½", 9, 9);
    locations[9][7] = new Place("ÀÇÉ½", 9, 7);
    locations[8][7] = new Road(true, 8, 7);
}

void Map::printPlainMap() const {
    for (int j = 0; j < 15; j++) {
        for (int i = 0; i < 15; i++) {
            cout.width(10);
            if (locations[i][j]->getType() == 'b') cout << ' ';
            else if (locations[i][j]->getType() == 'p') cout << (static_cast<Place *>(locations[i][j]))->getName();
            else if (locations[i][j]->getType() == 'r')
                cout << ((static_cast<Road *>(locations[i][j]))->getIsAccessible() ? "¡ö" : "¡õ");
        }
        cout << endl;
    }
}

void Map::printMap() const {

}




#endif //GAMETOWER_MAP_H
