//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_HERO_H
#define GAMETOWER1_HERO_H

// define static_cast<Road*>(map.getLocation(x,y))->getIsAccessible() to make it shorter
#define isAccessible(x,y) static_cast<Road*>(map.getLocation(x,y))->getIsAccessible()
#define getPlaceName(x,y) static_cast<Place*>(map.getLocation(x,y))->getName()
#define gotoPlace(x,y) "\33["<<(static_cast<Place*>(map.getLocation(x, y))->getX())<<";"<<(static_cast<Place*>(map.getLocation(x, y))->getY())<<"H"
#define isBarrier(x,y) !(map.getLocation(x,y)->isRoad() || map.getLocation(x,y)->isPlace())

#include <iostream>
#include <vector>
#include <conio.h>
#include "Backpack.h"
#include "Word.h"
#include "Creature.h"
#include "Map.h"

struct MapPosition {
    int line;
    int column;
};

class Player : public Creature {
public:
    Player();
    void Attack();
    void printMap() const;
    void move();
private:
    std::vector<Word> wordList;
    Backpack backpack;
    Map map;
    MapPosition pos = {8, 4};
    MapPosition lastPos = {8, 4};
};

Player::Player(): map(), Creature(100, "Alex"){}

void Player::printMap() const {
    map.printMap();
    PosControl::setPos(0,0);
    cout << "\33[47;33m" << "Alex Potter" << "\33[0m" << endl;
    cout << endl;
    cout << "\33[47;33m" << "HP: " << "\33[0m" << hp << endl;
    cout << "\33[47;33m" << "Backpack: " << "\33[0m" << endl;
    backpack.showItemList();
    cout << endl;
    cout << "按下 \033[31m[Q] \033[0m退出游戏" << endl << endl;
}

void Player::move() {
    char c;
    // 输入wasd，控制在地图中的位置
    while (1) {
        cout << "\33[2;10H                    \33[0m";
        cout << "\33[2;0H你现在在：" << getPlaceName(pos.line,pos.column) << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << gotoPlace(lastPos.line, lastPos.column) << getPlaceName(lastPos.line,lastPos.column) << "\33[0m" ;
        cout << gotoPlace(pos.line, pos.column) << "\33[43;37m" << getPlaceName(pos.line,pos.column) << "\33[0m" ;
        c = getch();
        switch (c) {
            case 'w':
            case 'W':
            case 72:
                pos.line--;
                if (pos.line > 0 && pos.line < 9) {
                    if (isBarrier(pos.line,pos.column)) {
                        pos.line++;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (isAccessible(pos.line,pos.column))
                    {
                        lastPos.line = pos.line+1;
                        lastPos.column = pos.column;
                        pos.line--;
                    }
                    else {
                        pos.line++;
                    }
                }
                else {
                    pos.line++;
                }
                break;
            case 'a':
            case 'A':
            case 75:
                pos.column--;
                if (pos.column > 0 && pos.column < 9) {
                    if (isBarrier(pos.line,pos.column)) {
                        pos.column++;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (isAccessible(pos.line,pos.column))
                    {
                        lastPos.column = pos.column+1;
                        lastPos.line = pos.line;
                        pos.column--;
                    }
                    else {
                        pos.column++;
                    }
                }
                else {
                    pos.column++;
                }
                break;
            case 's':
            case 'S':
            case 80:
                pos.line++;
                if (pos.line < 9 && pos.line > 0) {
                    if (isBarrier(pos.line,pos.column)) {
                        pos.line--;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (isAccessible(pos.line,pos.column))
                    {
                        lastPos.line = pos.line-1;
                        lastPos.column = pos.column;
                        pos.line++;
                    }
                    else {
                        pos.line--;
                    }
                }
                else {
                    pos.line--;
                }
                break;
            case 'd':
            case 'D':
            case 77:
                pos.column++;
                if (pos.column < 9 && pos.column > 0) {
                    if (isBarrier(pos.line,pos.column)) {
                        pos.column--;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (isAccessible(pos.line,pos.column))
                    {
                        lastPos.column = pos.column-1;
                        lastPos.line = pos.line;
                        pos.column++;
                    }
                    else {
                        pos.column--;
                    }
                }
                else {
                    pos.column--;
                }
                break;
            case 'q':
            case 'Q':
                // TODO: 保存进度
                exit(0);
            default:
                break;
        }
    }
}


#endif //GAMETOWER1_HERO_H
