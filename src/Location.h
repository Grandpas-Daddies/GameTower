//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_LOCATION_H
#define GAMETOWER_LOCATION_H

#include <string>
#include <fstream>
#include "FightScene.h"

using std::string;

class Location {
public:
    Location() { type = 'b'; };

    bool isRoad() const { return type == 'r'; }

    bool isPlace() const { return type == 'p'; }

    virtual bool getIsAccessible() const { return false; }

    virtual string getName() const { return ""; }

    virtual int getX() const { return 0; }

    virtual int getY() const { return 0;}

    virtual ~Location() = default;

protected:
    char type;
};

class Road : public Location {
public:
    Road(bool isAccessible) : isAccessible(isAccessible) { type = 'r'; };

    bool getIsAccessible() const final { return isAccessible; }

//    void setIsAccessible(bool isAccessible) { this->isAccessible = isAccessible; }

private:
    bool isAccessible;
};

class Place : public Location {
public:
    Place(string name, int x, int y, bool isHidden = false) : x(x), y(y), name(name), isHidden(isHidden) {
        type = 'p'; //place
    };

    string getName() const final { return name; }

    int getX() const final { return x; }

    int getY() const final { return y; }

private:
    int x;
    int y;
    string name;
    bool isHidden = false;
};

#endif //GAMETOWER_LOCATION_H
