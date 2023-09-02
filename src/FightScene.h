//
// Created by xiao on 2023-08-21.
//

#ifndef GAMETOWER1_FIGHT_SCENE_H
#define GAMETOWER1_FIGHT_SCENE_H

#include <vector>
#include "Monster.h"
#include <time.h>
#include <random>
//#include "Player.h"
#include "Interface.h"
#include "Word.h"
#include "Player.h"

void cls() {
    for (int i = 1; i <= 15; i++) {
        PosControl::setPos(i, 1);
        for (int j = 1; j < 101; j++) {
            cout << ' ';
        }
    }
    for (int i = 1; i <= 15; i++) {
        PosControl::setPos(i + 21, 1);
        for (int j = 1; j < 101; j++) {
            cout << ' ';
        }
    }
}

void updatePrint(std::vector<Word> upper, std::vector<Word> lower) {
    //cls();
    for (int i = 0; i < upper.size(); i++) {
        PosControl::setPos(i + 1, 1);
        upper[i].putWord();
        PosControl::setPos(i + 22, 1);
        lower[i].putWord();
    }
}

int deeper(int &t, Word &word, std::vector<Word> &upper, std::vector<Word> &lower) {
    while (t-- >= 0) {
        char next = ' ';
        int cur = word.getCur();
        Sleep(5);
        if (_kbhit()) {
            next = _getch();
        }
        if (next == word.getString()[cur]) {
            word.changeColor(cur, 5);
            word.changeCur(cur + 1);
            updatePrint(upper, lower);
        } else if (next == ' ') {

        } else {
            for (int i = 0; i < cur; i++) {
                word.changeColor(i, 8);
            }
            word.changeCur(0);
            updatePrint(upper, lower);
            return -1;
        }
        if (cur == word.getLength())return 0;
    }
    return 0;
}

void HideCursor() {
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle, &cursor);
}

class FightScene {
public:
    FightScene(string name) : name(name) {}

    void loadScene(Player &player);

    void showScene();//不停清屏展示新内容
    void showTutorial();//展示教程
    void fallingDown(int speed1, int speed2, std::vector<Word> upper, std::vector<Word> lower);

    void typeAndColor(std::vector<Word> &upper, std::vector<Word> &lower);

private:
    Monster monster;//本关所面对的怪物
    std::string name;

};

void FightScene::typeAndColor(std::vector<Word> &upper, std::vector<Word> &lower) {
    int t = 100;
    char next = ' ';
    while (t-- >= 0) {
        Sleep(5);
        next = ' ';
        if (_kbhit()) {
            next = _getch();
        }
        if (next <= 'z' && next >= 'a') {
            int flag = 0, flag2 = 0;
            for (int i = upper.size() - 1; i >= 0; i--) {
                int cur = upper[i].getCur();
                if (!upper[i].getState() && cur != 0) {
                    flag2 = 1;
                    if (upper[i].getString()[cur] == next) {
                        upper[i].changeColor(upper[i].getCur(), 5);
                        upper[i].changeCur(cur + 1);
                        updatePrint(upper, lower);
                        int state = deeper(t, upper[i], upper, lower);
                        if (state == -1) {
                            flag = 1;
                            flag2 = 0;
                            break;
                        } else if (state == 0 && upper[i].getCur() == upper[i].getLength()) {
                            upper[i].changeState(1);
                            updatePrint(upper, lower);
                            flag2 = 0;
                            break;
                            //补写effects
                        }
                    } else {
                        for (int j = 0; j < upper[i].getCur(); j++) {
                            upper[i].changeColor(j, 8);
                        }
                        upper[i].changeCur(0);
                        updatePrint(upper, lower);
                        flag = 1;
                        break;
                    }
                }
            }
            for (int i = upper.size() - 1; i >= 0; i--) {
                if (flag)break;
                if (flag2)break;
                if (!upper[i].getState() && next == upper[i].getString()[0] && !upper[i].getCur()) {
                    upper[i].changeColor(0, 5);
                    upper[i].changeCur(1);
                    updatePrint(upper, lower);
                    int state = deeper(t, upper[i], upper, lower);
                    if (state == -1) {
                        break;
                    } else if (state == 0 && upper[i].getCur() == upper[i].getLength()) {
                        upper[i].changeState(1);
                        updatePrint(upper, lower);
                        break;
                        //补写effects
                    }
                }
            }
        } else if (next <= 'Z' && next >= 'A') {
            int flag = 0, flag2 = 0;
            for (int i = lower.size() - 1; i >= 0; i--) {
                int cur = lower[i].getCur();
                if (!lower[i].getState() && cur != 0) {
                    flag2 = 1;
                    if (lower[i].getString()[cur] == next) {
                        lower[i].changeColor(lower[i].getCur(), 5);
                        lower[i].changeCur(cur + 1);
                        updatePrint(upper, lower);
                        int state = deeper(t, lower[i], upper, lower);
                        if (state == -1) {
                            flag = 1;
                            flag2 = 0;
                            break;
                        } else if (state == 0 && lower[i].getCur() == upper[i].getLength()) {
                            lower[i].changeState(1);
                            updatePrint(upper, lower);
                            flag2 = 0;
                            break;
                            //补写effects
                        }
                    } else {
                        for (int j = 0; j < lower[i].getCur(); j++) {
                            lower[i].changeColor(j, 8);
                        }
                        lower[i].changeCur(0);
                        updatePrint(upper, lower);
                        flag = 1;
                        break;
                    }
                }
            }
            for (int i = lower.size() - 1; i >= 0; i--) {
                if (flag)break;
                if (flag2)break;
                if (!lower[i].getState() && next == lower[i].getString()[0] && !lower[i].getCur()) {
                    lower[i].changeColor(0, 5);
                    lower[i].changeCur(1);
                    updatePrint(upper, lower);
                    int state = deeper(t, lower[i], upper, lower);
                    if (state == -1) {
                        break;
                    } else if (state == 0 && lower[i].getCur() == upper[i].getLength()) {
                        lower[i].changeState(1);
                        updatePrint(upper, lower);
                        break;
                        //补写effects
                    }
                }
            }
        } else if (next <= '9' && next >= '0') {

        }

    }
}

void FightScene::loadScene(Player &player) {
    showScene();
    //showTutorial();

    HideCursor();

    //创造一个monster，后期改为读取
    std::vector<Word> temp;
    Word word5(7, "AIRISGO", 'd');
    Word word6(6, "ATTACK", 'd');
    Word word7(5, "BADPE", 'd');
    Word word8(2, "HAHA", 'd');
    Word word1(7, "airisgo", 'd');
    Word word2(6, "attack", 'd');
    Word word3(5, "badpe", 'd');
    Word word4(2, "ha", 'd');
    temp.push_back(word1);
    temp.push_back(word2);
    temp.push_back(word3);
    temp.push_back(word4);
    temp.push_back(word1);
    temp.push_back(word2);
    temp.push_back(word3);
    temp.push_back(word4);
    Monster tutorialMonster(2, 4, temp);
    std::vector<Word> upper, lower;

    //lower = player.deliverWord();
    lower.push_back(word5);
    lower.push_back(word6);
    lower.push_back(word7);
    lower.push_back(word8);
    lower.push_back(word5);
    lower.push_back(word6);
    lower.push_back(word7);
    lower.push_back(word8);
    upper = tutorialMonster.deliverWord();
    while (player.getHP() != 0 && tutorialMonster.getHP() != 0) {
        srand((unsigned int) time(NULL));
        int j = 0;
        for (int i = 0; i < upper.size(); i++) {
            j = rand() % upper.size();
            Word tmp = upper[j];
            upper[j] = upper[i];
            upper[i] = tmp;

            tmp = lower[j];
            lower[j] = lower[i];
            lower[i] = tmp;
        }
        for (int i = 0; i < upper.size(); i++) {
            upper[i].changeCur(0);
            lower[i].changeCur(0);
            upper[i].changeState(0);
            lower[i].changeState(0);
            for (int j = 0; j < lower[i].getLength(); j++) {
                lower[i].changeColor(j, 8);
            }
            for (int i = 0; i < upper[i].getLength(); i++) {
                upper[i].changeColor(j, 8);
            }
        }
        fallingDown(1, 1, upper, lower);
    }

    system("pause");

}

void FightScene::fallingDown(int speed1, int speed2, std::vector<Word> upper, std::vector<Word> lower) {
    //分两部分：怪物攻击侧的check及结算，玩家侧的check及结算。

    Word blank(-1, "", ' ');//特殊白板，长度为-1，与常规白板作区分
    std::vector<Word> shownUpper, shownLower;
    for (int i = 0; i < 15; i++) {
        shownUpper.push_back(blank);
        shownLower.push_back(blank);
    }
    int cur = 0, offset = 0;
    while (cur < upper.size()) {
        for (int i = shownUpper.size() - 1; i > 0; i--) {
            shownUpper[i] = shownUpper[i - 1];
            shownLower[i] = shownLower[i - 1];
        }

        offset = (offset + 1) % 2;
        if (offset) {
            shownUpper[0] = upper[cur];
            shownLower[0] = lower[cur];
            cur++;
        }
        for (int i = offset; i < shownUpper.size(); i += 2) {
            shownUpper[i] = blank;
            shownLower[i] = blank;
        }
        for (int i = 0; i < shownUpper.size(); i++) {
            PosControl::setPos(i + 1, 1);
            shownUpper[i].putWord();
            PosControl::setPos(i + 22, 1);
            shownLower[i].putWord();
        }
        typeAndColor(shownUpper, shownLower);
        cls();
    }
    while (1) {
        for (int i = shownUpper.size() - 1; i > 0; i--) {
            shownUpper[i] = shownUpper[i - 1];
            shownLower[i] = shownLower[i - 1];
        }
        offset = (offset + 1) % 2;
        for (int i = offset; i < shownUpper.size(); i += 2) {
            shownUpper[i] = blank;
            shownLower[i] = blank;
        }
        for (int i = 0; i < shownUpper.size(); i++) {
            PosControl::setPos(i + 1, 1);
            shownUpper[i].putWord();
            PosControl::setPos(i + 22, 1);
            shownLower[i].putWord();
        }
        int cnt = 0;
        for (int i = 0; i < shownUpper.size(); i++) {
            if (shownUpper[i].getLength() == -1)cnt++;
            if (shownLower[i].getLength() == -1)cnt++;
        }
        if (cnt == shownUpper.size() * 2)break;
        typeAndColor(shownUpper, shownLower);
        cls();
    }
}

void FightScene::showScene() {
    system("cls");
    ifstream sceneFile("./Assets/.fightScene");
    string scene;
    while (getline(sceneFile, scene)) {
        cout << scene << endl;
    }
    sceneFile.close();
}

void FightScene::showTutorial() {
    std::cout << "教程" << std::endl;
}

#endif //GAMETOWER1_FIGHT_SCENE_H
