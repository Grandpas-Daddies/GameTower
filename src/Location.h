//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_LOCATION_H
#define GAMETOWER_LOCATION_H

#include <string>

using std::string;

class Location {
public:
    Location() {
        type = 'b'; //barrier
    };

    bool isPlace() const {
        return type == 'p';
    }

    bool isRoad() const {
        return type == 'r';
    }

protected:
    char type;
    bool isHighlighted = false;
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
    Place(string name, bool isHidden = false) : name(name), isHidden(isHidden) {
        type = 'p'; //place
    };

    string getName() const {
        return name;
    };
private:
    string name;
    bool isHidden = false;
};

#endif //GAMETOWER_LOCATION_H
