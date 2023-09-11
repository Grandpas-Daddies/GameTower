//
// Created by xiao on 2023-08-21.
//

#ifndef GAMETOWER1_FIGHT_SCENE_H
#define GAMETOWER1_FIGHT_SCENE_H
#define getPlaceName(x, y) dynamic_cast<Place*>(map.getLocation(x,y))->getName()

#include <vector>
#include "Monster.h"
#include <time.h>
#include <random>
#include "Interface.h"
#include "Word.h"
#include "Player.h"
#include "Map.h"
#include "Behavior.h"

void cls();

void updatePrint(std::vector<Word> upper, std::vector<Word> lower);

int deeper(int &t, Word &word, std::vector<Word> &upper, std::vector<Word> &lower);


class FightScene {
public:
    FightScene(string name, int progress) : name(name), monster(progress + 1) {};

//    FightScene(std::string id, int b);

    void loadScene(Player &player);//外部调用接口
    bool checkWin(Player &player);

    void showScene();//展示框架，由loadScene调用
    void showTutorial();//展示教程，视情况由loadScene调用
    void
    fallingDown(int speed1, int speed2, const std::vector<Word> &upper, const std::vector<Word> &lower, Player &player);

    //字符下落，由loadScene调用

    //调控打字变色并check，由loadScene调用
    void showHP(Player &player);

    ~FightScene() = default;

private:
    Monster monster;//本关所面对的怪物
    std::string name;

    void showScene(Backpack &backpack);

    void typeAndColor(std::vector<Word> &upper, std::vector<Word> &lower, Player &player);

    void useItem(Player &player, int effect);
};

void FightScene::showHP(Player &player) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    PosControl::setPos(16, 1);
    cout << "MonsterHP:";
    int curhp, HP;
    curhp = std::max(0, monster.getCurrHP()), HP = monster.getHP();
    cout << curhp << '/' << HP;
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    PosControl::setPos(16, 1);
    cout << "MonsterHP:";
    cout << curhp << '/' << HP;
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }
    PosControl::setPos(21, 1);
    curhp = std::max(0, player.getCurrHP()), HP = player.getHP();
    cout << "PlayerHP:";
    cout << curhp << '/' << HP;
    for (int i = 0; i < HP * 80 / HP; i++) {
        cout << '_';
    }
    PosControl::setPos(21, 1);
    cout << "PlayerHP:";
    cout << curhp << '/' << HP;
    for (int i = 0; i < curhp * 80 / HP; i++) {
        cout << '*';
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
}

void FightScene::loadScene(Player &player) {//最主要的函数，万物的起源
    showScene(player.getBackpack());//打印一下边框

    PosControl::HideCursor();//隐藏光标

    std::vector<Word> upper, lower;//核心单词表，直接源自monster和player，分别代表上下
    upper = monster.deliverWord();
    lower = player.deliverWord();

    showHP(player);//显示初始血量
    while (player.getCurrHP() > 0 && monster.getCurrHP() > 0) {//战斗循环，只要都没死就一直进行
        int j = 0;
        for (int i = 0; i < upper.size(); i++) {
            j = randInt(0, 100) % upper.size();
            Word tmp = upper[j];
            upper[j] = upper[i];
            upper[i] = tmp;

            tmp = lower[j];
            lower[j] = lower[i];
            lower[i] = tmp;
        }//258~296作用是将词库打乱；
        for (int i = 0; i < upper.size(); i++) {
            upper[i].changeCur(0);
            lower[i].changeCur(0);
            upper[i].changeState(0);
            lower[i].changeState(0);
            for (int j = 0; j < lower[i].getLength(); j++) {
                lower[i].changeColor(j, 8);
            }
            for (int k = 0; k < upper[i].getLength(); k++) {
                upper[i].changeColor(k, 8);
            }
        }//将词库初始化
        fallingDown(1, 1, upper, lower, player);//speed暂时没有用，
        //fallingDown是控制词往下掉的函数。

    }
    return;
}

void FightScene::fallingDown(int speed1, int speed2, const std::vector<Word> &upper, const std::vector<Word> &lower,
                             Player &player) {
    //分两部分：怪物攻击侧的check及结算，玩家侧的check及结算。

    Word blank(-1, "", ' ');//特殊白板，长度为-1，与常规白板作区分
    std::vector<Word> shownUpper, shownLower;
    //单纯的词库有两个问题：1.一开始肯定不能全部输出，那我缺失这些空白没有人弥补；
    //  2.跑完一圈不好收拾，
    //  3.一行一个太挤，一行两个做不到。
    // 因此，使用shown系列表示具体区域，用白板表示空行，输出也方便。
    for (int i = 0; i < 15; i++) {
        shownUpper.push_back(blank);
        shownLower.push_back(blank);
    }//先给上下都填上空白，之后再单双填词，以实现隔一行的效果
    int cur = 0, offset = 0;//这个cur用来判断当前进行到哪一个单词了
    while (cur < upper.size()) {//这是第一部分，词还没有完全进入shown区域内。
        if (shownUpper[shownUpper.size() - 1].getState() == 0 && shownUpper[shownUpper.size() - 1].getLength() > 0) {
            player.getDamaged(monster.getDamage());
            showHP(player);
        }//人物扣血的判定
        for (int i = shownUpper.size() - 1; i > 0; i--) {
            shownUpper[i] = shownUpper[i - 1];
            shownLower[i] = shownLower[i - 1];
        }//替换词，向下一行

        offset = (offset + 1) % 2;//offset在0和1之间变换，用来实现每两回合加入一个单词的设定
        if (offset) {
            shownUpper[0] = upper[cur];
            shownLower[0] = lower[cur];
            cur++;
        }
        for (int i = offset; i < shownUpper.size(); i += 2) {//有重复加入的bug，所以把应该是白板的地方重新塞了白板
            shownUpper[i] = blank;
            shownLower[i] = blank;
        }
        for (int i = 0; i < shownUpper.size(); i++) {
            PosControl::setPos(i + 1, 1);
            shownUpper[i].putWord();
            PosControl::setPos(i + 22, 1);
            shownLower[i].putWord();
        }//输出一遍当前的shown
        typeAndColor(shownUpper, shownLower, player);//核心函数，判断打字用的

        cls();//手写的清屏，只清打字的区域
        PosControl::setPos(17, 0);
        player.getBackpack().printItemList(1);
        showHP(player);//展示血量
        if (monster.getCurrHP() <= 0 || player.getCurrHP() <= 0)
            return;//死亡判断
    }
    while (1) {//这里跟上面的while其实差不多，只是不再塞入新的词，而是把已经在里面的词跑完。
        if (shownUpper[shownUpper.size() - 1].getState() == 0 && shownUpper[shownUpper.size() - 1].getLength() > 0) {
            player.getDamaged(monster.getDamage());
            showHP(player);
        }
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
        typeAndColor(shownUpper, shownLower, player);
        cls();
        showHP(player);
        if (monster.getCurrHP() <= 0 || player.getCurrHP() <= 0)return;

    }
}

void FightScene::typeAndColor(std::vector<Word> &upper, std::vector<Word> &lower, Player &player) {
    int t = 100;//hjr的妙手，通过多段短暂的sleep在一次刷屏间隙中能打多个字母
    char next = ' ';//next是下一个键盘敲得字符
    int itemClock[10] = {0};
    while (t-- >= 0) {
        Sleep(5);
        next = ' ';
        if (_kbhit()) {//get键盘字符
            next = _getch();
        }
        if (next <= 'z' && next >= 'a') {//小写字母，对应下面
            bool existWrong = 0, existUnfinished = 0;//两个状态量，本次循环中是否存在打错，是否存在打了一半的词
            for (int i = lower.size() - 1; i >= 0; i--) {//未打完的字具有优先性，所以先循环一遍找有没有未打完的
                int cur = lower[i].getCur();//这里的cur是词的状态，表示当前打了几个字符，通常为0；
                if (!lower[i].getState() && cur != 0) {//如果有一个词没打完，cur也不是0，说明找到了未打完的词
                    existUnfinished = 1;//改状态
                    if (lower[i].getString()[cur] == next) {//如果下一位和键盘敲得匹配成功
                        lower[i].changeColor(lower[i].getCur(), 5);//染色
                        lower[i].changeCur(cur + 1);//进一位
                        updatePrint(upper, lower);//重新输出，更新显示的颜色
                        int state = deeper(t, lower[i], upper, lower);//调用deeper，对当前单词进行进一步匹配，并返回状态
                        if (state == -1) {//deeper进行时打错字了
                            existWrong = 1;//存在错误
                            existUnfinished = 0;//打错了回到解放前，所以不存在没有完成的词了
                            break;
                        } else if (state == 0 && lower[i].getCur() == lower[i].getLength()) {//写完了
                            lower[i].changeState(1);//标记已完成
                            updatePrint(upper, lower);//genshin
                            existUnfinished = 0;//不存在没完成的词了
                            monster.getDamaged(lower[i].getEffect());//攻击侧结算应该写好了
                            break;
                            //补写effects （好像effects也改好了
                        } else {
                            //疑似是啥也不用干
                        }
                    } else {//没进deeper，直接打错字了
                        for (int j = 0; j < lower[i].getCur(); j++) {//基本同上
                            lower[i].changeColor(j, 8);
                        }
                        lower[i].changeCur(0);
                        updatePrint(upper, lower);
                        existWrong = 1;
                        existUnfinished = 0;
                        break;
                    }
                }
                if (existUnfinished)break;//如果存在没打完的词，就往后看了，不然会出现同时有多个未打完的词的情况。
            }
            for (int i = lower.size() - 1; i >= 0; i--) {//对于完整的词的判断。
                if (existWrong || existUnfinished)break;//在这里也会有打错和没打完的情况，所以循环内也要写。
                if (!lower[i].getState() && next == lower[i].getString()[0] && !lower[i].getCur()) {//后面大差不差
                    lower[i].changeColor(0, 5);
                    lower[i].changeCur(1);
                    updatePrint(upper, lower);
                    int state = deeper(t, lower[i], upper, lower);
                    if (state == -1) {
                        break;
                    } else if (state == 0 && lower[i].getCur() == lower[i].getLength()) {
                        lower[i].changeState(1);
                        updatePrint(upper, lower);
                        monster.getDamaged(lower[i].getEffect()); //不知道和上面有什么区别但我还是顺手改的和236一样了
                        break;
                        //补写effects
                    } else {
                        existUnfinished = 1;
                    }
                }
            }
        } else if (next <= 'Z' && next >= 'A') {//跟小写情况差不多
            bool existWrong = 0, existUnfinished = 0;
            for (int i = upper.size() - 1; i >= 0; i--) {
                int cur = upper[i].getCur();
                if (!upper[i].getState() && cur != 0) {
                    existUnfinished = 1;
                    if (upper[i].getString()[cur] == next) {
                        upper[i].changeColor(upper[i].getCur(), 5);
                        upper[i].changeCur(cur + 1);
                        updatePrint(upper, lower);
                        int state = deeper(t, upper[i], upper, lower);
                        if (state == -1) {//deeper进行时打错字了
                            existWrong = 1;
                            existUnfinished = 0;
                            break;
                        } else if (state == 0 && upper[i].getCur() == upper[i].getLength()) {
                            upper[i].changeState(1);
                            updatePrint(upper, lower);
                            existUnfinished = 0;
                            break;
                            //补写effects
                        } else {
                            //疑似是啥也不用干
                        }
                    } else {//没进deeper，直接打错字了
                        for (int j = 0; j < upper[i].getCur(); j++) {
                            upper[i].changeColor(j, 8);
                        }
                        upper[i].changeCur(0);
                        updatePrint(upper, lower);
                        existWrong = 1;
                        existUnfinished = 0;
                        break;
                    }
                }
                if (existUnfinished)break;
            }
            for (int i = upper.size() - 1; i >= 0; i--) {
                if (existWrong || existUnfinished)break;
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
                    } else {
                        existUnfinished = 1;
                    }
                }
            }

        } else if (next <= '9' && next >= '0') {

            if (itemClock[next - '0'] == 0) {
                if (player.getBackpack().isItemExist(next - '0')) {
                    if (!player.getBackpack().useItem(next - '0'))
                        useItem(player, player.getBackpack().getItemEffect(next - '0'));
                }
            }
            if (player.getBackpack().isItemExist(next - '0'))
                itemClock[next - '0'] = player.getBackpack().getItemClock(next - '0');
        }
        for (int i = 0; i < 10; i++) {
            if (itemClock[i] > 0) {
                itemClock[i]--;
            }
        }

    }
}

void FightScene::useItem(Player &player, int effect) {

    if (effect > 0) {
        player.getDamaged(-effect);
        if (player.getCurrHP() > player.getHP()) {
            player.resetCurrHP();
        }
    }
    if (effect < 0) {
        monster.getDamaged(-effect);
    }
    return;
}

void FightScene::showScene(Backpack &backpack) {
    system("cls");
    ifstream sceneFile("./Assets/.fightScene");
    string scene;
    while (getline(sceneFile, scene)) {
        cout << scene << endl;
    }
    sceneFile.close();
    PosControl::setPos(17, 0);
    printMsg("./Assets/Scene/BeforeFight/" + name + ".txt", true);
    PosControl::setPos(17, 0);
    // 清除四行
    for (int i = 0; i < 4; i++) {
        cout << "\33[2K" << endl;
    }
    PosControl::setPos(17, 0);
    backpack.printItemList(1);
}

void FightScene::showTutorial() {
    std::cout << "教程" << std::endl;
}

bool FightScene::checkWin(Player &player) {
    if (player.getCurrHP() <= 0) return 0;
    return 1;
}

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
    while (t-- >= 0) {//继承表示次数的t，确保每次下落时间的统一性
        char next = ' ';//操作几乎一样，也很容易理解
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

#endif //GAMETOWER1_FIGHT_SCENE_H
