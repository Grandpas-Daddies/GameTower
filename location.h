//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_LOCATION_H
#define GAMETOWER_LOCATION_H

#include <string>

using std::string;

class Location {
public:
    Location(int x, int y) : x(x), y(y) {
        type = 'b'; //barrier
    };

    char getType() const {
        return type;
    };

private:
    int x;
    int y;
protected:
    char type;
};

class Road : public Location {
public:
    Road(bool isAccessible, int x, int y) : Location(x, y), isAccessible(isAccessible) {
        type = 'r'; //road
    };

    bool getIsAccessible() const {
        return isAccessible;
    }

    void setIsAccessible(bool isAccessible) {
        this->isAccessible = isAccessible;
    }

private:
    bool isAccessible;
};

class Place : public Location {
public:
    Place(string name, int x, int y) : Location(x, y), name(name) {
        type = 'p'; //place
    };

    string getName() const {
        return name;
    };
private:
    string name;
};

#endif //GAMETOWER_LOCATION_H
