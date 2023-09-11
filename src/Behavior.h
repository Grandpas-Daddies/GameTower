//
// Created by Jiarong on 2023/8/29.
//

#ifndef GAMETOWER_BEHAVIOR_H
#define GAMETOWER_BEHAVIOR_H
//#define У�� 8,4
//#define ӭ�´��� 6,4
//#define �칦����� 4,4
//#define ʥ̳ 2,4
//#define սǰ׼��Ӫ�� 4,2
//#define ���ܻ����� 4,6
//#define ���ص�ħ��Ĺ�� 2,6

#define ifAccessible(x, y) dynamic_cast<Road*>(map.getLocation(x,y))->getIsAccessible()
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()
#define gotoPlace(x, y) "\33["<<(dynamic_cast<Place*>(map.getLocation(x, y))->getX())<<";"<<(dynamic_cast<Place*>(map.getLocation(x, y))->getY())<<"H"
#define isBarrier(x, y) !(map.getLocation(x,y)->isRoad() || map.getLocation(x,y)->isPlace())
#define ifHasDone(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getHasDone()
#define getIsLocked(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getIsLocked()


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
        map.setProgress(map.getProgress());
        player.printStatus();
        cout << "current progress: " << map.getProgress() << endl;
        cout << "\33[2;10H                    \33[0m";
        cout << "\33[2;0H��ǰλ�ã�" << getPlaceName(pos.line, pos.column) << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << gotoPlace(lastPos.line, lastPos.column) << getPlaceName(lastPos.line, lastPos.column) << "\33[0m";
        cout << gotoPlace(pos.line, pos.column) << "\33[43;37m" << getPlaceName(pos.line, pos.column) << "\33[0m";
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
            case 'b':
            case 'B': {
                system("cls");
//                printMsg("./Assets/.avatar", 0, 1);
                player.getBackpack().printItemList(0);
                system("pause");
                Map::printMap();
                break;
            }
            case 'l':
            case 'L': {
                system("cls");
//                printMsg("./Assets/.avatar", 0, 1);
                player.printWordList();
                system("pause");
                Map::printMap();
                break;
            }
            case 'e':
            case 'E': {
                system("cls");
                printMsg("./Assets/.help");
                system("pause");
                Map::printMap();
                break;
            }
            case 'n':
            case 'N': {
                system("cls");
                printMsg("./Assets/.monsterDescription");
                system("pause");
                Map::printMap();
                break;
            }
            case '\r':
            case '\n': {
                system("cls");
                if (getIsLocked(pos.line, pos.column)) {

                    if (map.getProgress() < 3 && pos.line == 4 && pos.column == 2) {
                        printMsg("./Assets/Scene/Other/Ӫ��δ����.txt");
                    } else if (map.getProgress() == 4 || map.getProgress() == 5) {
                        printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                    } else {
                        printMsg(map.getDefaultMsgDir());
                    }
                    system("pause");
                } else {
                    if (ifHasDone(pos.line, pos.column)) {
                        printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                        system("pause");
                    } else {
                        if (map.getProgress() == 2 && pos.line == 4 && pos.column == 4) {
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                            system("pause");
                            system("cls");
                            lastPos = {4, 4}; // �칦�����
                            pos = {4, 6}; // ���ܻ�����
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() == 2 && pos.line == 4 && pos.column == 6) {
                            lastPos = {4, 4};
                            pos = {4, 4};
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                            system("pause");
                            system("cls");
                            pos = {4, 6};
                            printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() == 3 && pos.line != 2 && pos.column != 6) {
                            printMsg("./Assets/Scene/Other/ս����־.txt");
                        } else if (map.getProgress() == 4 && pos.line == 4 && pos.column == 4) {
                            if (getIsLocked(2,4))
                                printMsg("./Assets/Scene/Other/��ս��Ϣ.txt");
                            else printMsg("./Assets/Scene/Default/" + getPlaceName(pos.line, pos.column) + ".txt");
                        } else if (map.getProgress() < 4 && pos.line == 2 && pos.column == 4) {
                            printMsg("./Assets/Scene/Other/ȥ������.txt");
                        } else printMsg("./Assets/Scene/Background/" + getPlaceName(pos.line, pos.column) + ".txt");
                        system("pause");

                        if (map.getProgress() == 4 && pos.line == 4 && pos.column == 2) {
                            player.getBackpack().progress4();
                            dynamic_cast<Place*>(map.getLocation(4,2))->setHasDone(true);
                            dynamic_cast<Place*>(map.getLocation(2,4))->setIsLocked(false);
                            dynamic_cast<Place*>(map.getLocation(4,4))->setIsLocked(true);
                        }

                        if ((pos.line == 4 && pos.column == 2) ||
                            (pos.line == 4 && pos.column == 4));
                        else {// FightScene

                            Backpack backupBackpack = player.getBackpack();
                            int backupCurrHP = player.getCurrHP();

                            FightScene *currFightScene = new FightScene(getPlaceName(pos.line, pos.column),
                                                                        map.getProgress());
                            currFightScene->loadScene(player);
                            if (currFightScene->checkWin(player)) {
                                system("cls");
                                map.setHasDone(pos.line, pos.column);
                                player.playerWordlist(player.getMap().getProgress() + 1);
                                printMsg("./Assets/Scene/Other/ʤ��.txt");
                                system("cls");
                                printMsg("./Assets/Scene/AfterFight/" + getPlaceName(pos.line, pos.column) + ".txt");
                                system("pause");
                            } else {
                                system("cls");
                                printMsg("./Assets/Scene/Other/ʧ��.txt");
                                player.setCurrHP(backupCurrHP);
                                player.setBackpack(backupBackpack);
                                system("pause");
                            }
                            delete currFightScene;
                        }
                    }
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
