//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_LOCATION_H
#define GAMETOWER_LOCATION_H

#include <string>

using std::string;

class Location {
public:
    Location() = default;

    bool isRoad() const {
        return type == 'r';
    }

    bool isPlace() const {
        return type == 'p';
    }

protected:
    char type;
//    bool isHighlighted = false;
};

class Road : public Location {
public:
    Road(bool isAccessible) : isAccessible(isAccessible) {
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
    Place(string name, int x, int y, bool isHidden = false) : x(x), y(y), name(name), isHidden(isHidden) {
        type = 'p'; //place
    };

    string getName() const {
        return name;
    };

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }
private:
    int x;
    int y;
    string name;
    bool isHidden = false;
};

#endif //GAMETOWER_LOCATION_H
