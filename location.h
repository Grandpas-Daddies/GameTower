//
// Created by Jiarong on 2023/8/21.
//

#ifndef GAMETOWER_LOCATION_H
#define GAMETOWER_LOCATION_H

#include <string>
using std::string;

class Location {
public:
    Location(string name, int x, int y);
    string getName() const;
    void setName(string name);
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    void setXY(int x, int y){
        this->x = x;
        this->y = y;
    };
    void initID(){
        id = x * 100 + y;
    }
private:
    string name;
    int x;
    int y;
    int id;
};

// locations are combined with roads and places
class Road : public Location {
public:
    Road(string name, bool isAccessible, int x, int y);
    bool getIsAccessible() const;
    void setIsAccessible(bool isAccessible);
private:
    bool isAccessible;
};

class Place : public Location {
public:
    Place(string name, bool isVisible, int x, int y);
    bool getIsVisible() const;
    void setIsVisible(bool isVisible);
private:
    bool isVisible;
};

#endif //GAMETOWER_LOCATION_H
