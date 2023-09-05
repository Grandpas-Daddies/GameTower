//
// Created by Jiarong on 2023/8/29.
//

#ifndef GAMETOWER_BEHAVIOR_H
#define GAMETOWER_BEHAVIOR_H

#define ifAccessible(x, y) dynamic_cast<Road*>(map.getLocation(x,y))->getIsAccessible()
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()
#define gotoPlace(x, y) "\33["<<(dynamic_cast<Place*>(map.getLocation(x, y))->getX())<<";"<<(dynamic_cast<Place*>(map.getLocation(x, y))->getY())<<"H"
#define isBarrier(x, y) !(map.getLocation(x,y)->isRoad() || map.getLocation(x,y)->isPlace())
#define ifHasDone(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getHasDone()
#define setHasDone(x, y, z) dynamic_cast<Place*>(map.getLocation(x,y))->setHasDone(z)

#include <iostream>
#include "Player.h"
#include "Interface.h"
#include "Map.h"
#include "FightScene.h"

using std::cout, std::endl;

void onMap(Player &player) {
    MapPosition &pos = player.getPos();
    MapPosition &lastPos = player.getLastPos();
    Map &map = player.getMap();
    char c;
    // wasd
    while (1) {
        player.printStatus();
        cout << "\33[2;10H                    \33[0m";
        cout << "\33[2;0H当前位置：" << getPlaceName(pos.line, pos.column) << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << gotoPlace(lastPos.line, lastPos.column) << getPlaceName(lastPos.line, lastPos.column) << "\33[0m";
        cout << gotoPlace(pos.line, pos.column) << "\33[43;37m" << getPlaceName(pos.line, pos.column) <<"\33[0m";
        c = getch();
        switch (c) {
            case 'w':
            case 'W':
            case 72: {
                pos.line--;
                if (pos.line > 0 && pos.line < 9) {
                    if (isBarrier(pos.line, pos.column)) {
                        pos.line++;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) {
                        lastPos.line = pos.line + 1;
                        lastPos.column = pos.column;
                        pos.line--;
                    } else {
                        pos.line++;
                    }
                } else {
                    pos.line++;
                }
                break;
            }
            case 'a':
            case 'A':
            case 75: {
                pos.column--;
                if (pos.column > 0 && pos.column < 9) {
                    if (isBarrier(pos.line, pos.column)) {
                        pos.column++;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) {
                        lastPos.column = pos.column + 1;
                        lastPos.line = pos.line;
                        pos.column--;
                    } else {
                        pos.column++;
                    }
                } else {
                    pos.column++;
                }
                break;
            }
            case 's':
            case 'S':
            case 80: {
                pos.line++;
                if (pos.line < 9 && pos.line > 0) {
                    if (isBarrier(pos.line, pos.column)) {
                        pos.line--;
                        lastPos.line = pos.line;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) {
                        lastPos.line = pos.line - 1;
                        lastPos.column = pos.column;
                        pos.line++;
                    } else {
                        pos.line--;
                    }
                } else {
                    pos.line--;
                }
                break;
            }
            case 'd':
            case 'D':
            case 77: {
                pos.column++;
                if (pos.column < 9 && pos.column > 0) {
                    if (isBarrier(pos.line, pos.column)) {
                        pos.column--;
                        lastPos.column = pos.column;
                        break;
                    }
                    if (ifAccessible(pos.line, pos.column)) {
                        lastPos.column = pos.column - 1;
                        lastPos.line = pos.line;
                        pos.column++;
                    } else {
                        pos.column--;
                    }
                } else {
                    pos.column--;
                }
                break;
            }
            case 'q':
            case 'Q': {
                return;
            }
                // F5
            case 63: {
                Map::printMap();
                break;
            }
            case '\r':
            case '\n': {
                if (ifHasDone(pos.line, pos.column)) {
                    system("cls");
                    printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                    system("pause");
                } else {
                    FightScene fightScene(getPlaceName(pos.line, pos.column));
                    fightScene.loadScene(player);
                    // TODO: 加返回值标识是否胜利
                    setHasDone(pos.line, pos.column, 1);
                }
                Map::printMap();
                break;
            }
            default:
                break;
        }
    }
}

#endif //GAMETOWER_BEHAVIOR_H
