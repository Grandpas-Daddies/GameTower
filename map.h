//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_MAP_H
#define GAMETOWER_MAP_H

#include "location.h"

class Map {
public:
    Map();
private:
    Location *locations[15][15];
};

Map::Map() {
    // map should be initialized with locations, which are combined with roads and places
    // roads are initialized with name, isAccessible
    // places are initialized with name, isVisible
    // roads are those whose 'x' is even or 'y' is even
    // places are those which is not a road

    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++) {
            if (i % 2 == 0 || j % 2 == 0) {
                locations[i][j] = new Road("Road", false, i+1, j+1);
            } else {
                locations[i][j] = new Place("Place", true, i+1, j+1);
            }
        }
    }


}

#endif //GAMETOWER_MAP_H
