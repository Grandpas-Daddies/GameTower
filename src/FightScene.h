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

    void loadScene(Player &player);//�ⲿ���ýӿ�
    bool checkWin(Player &player);

    void showScene();//չʾ��ܣ���loadScene����
    void showTutorial();//չʾ�̳̣��������loadScene����
    void
    fallingDown(int speed1, int speed2, const std::vector<Word> &upper, const std::vector<Word> &lower, Player &player);

    //�ַ����䣬��loadScene����

    //���ش��ֱ�ɫ��check����loadScene����
    void showHP(Player &player);

    ~FightScene() = default;

private:
    Monster monster;//��������ԵĹ���
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

void FightScene::loadScene(Player &player) {//����Ҫ�ĺ������������Դ
    showScene(player.getBackpack());//��ӡһ�±߿�

    PosControl::HideCursor();//���ع��

    std::vector<Word> upper, lower;//���ĵ��ʱ�ֱ��Դ��monster��player���ֱ��������
    upper = monster.deliverWord();
    lower = player.deliverWord();

    showHP(player);//��ʾ��ʼѪ��
    while (player.getCurrHP() > 0 && monster.getCurrHP() > 0) {//ս��ѭ����ֻҪ��û����һֱ����
        int j = 0;
        for (int i = 0; i < upper.size(); i++) {
            j = randInt(0, 100) % upper.size();
            Word tmp = upper[j];
            upper[j] = upper[i];
            upper[i] = tmp;

            tmp = lower[j];
            lower[j] = lower[i];
            lower[i] = tmp;
        }//258~296�����ǽ��ʿ���ң�
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
        }//���ʿ��ʼ��
        fallingDown(1, 1, upper, lower, player);//speed��ʱû���ã�
        //fallingDown�ǿ��ƴ����µ��ĺ�����

    }
    return;
}

void FightScene::fallingDown(int speed1, int speed2, const std::vector<Word> &upper, const std::vector<Word> &lower,
                             Player &player) {
    //�������֣����﹥�����check�����㣬��Ҳ��check�����㡣

    Word blank(-1, "", ' ');//����װ壬����Ϊ-1���볣��װ�������
    std::vector<Word> shownUpper, shownLower;
    //�����Ĵʿ����������⣺1.һ��ʼ�϶�����ȫ�����������ȱʧ��Щ�հ�û�����ֲ���
    //  2.����һȦ������ʰ��
    //  3.һ��һ��̫����һ��������������
    // ��ˣ�ʹ��shownϵ�б�ʾ���������ðװ��ʾ���У����Ҳ���㡣
    for (int i = 0; i < 15; i++) {
        shownUpper.push_back(blank);
        shownLower.push_back(blank);
    }//�ȸ����¶����Ͽհף�֮���ٵ�˫��ʣ���ʵ�ָ�һ�е�Ч��
    int cur = 0, offset = 0;//���cur�����жϵ�ǰ���е���һ��������
    while (cur < upper.size()) {//���ǵ�һ���֣��ʻ�û����ȫ����shown�����ڡ�
        if (shownUpper[shownUpper.size() - 1].getState() == 0 && shownUpper[shownUpper.size() - 1].getLength() > 0) {
            player.getDamaged(monster.getDamage());
            showHP(player);
        }//�����Ѫ���ж�
        for (int i = shownUpper.size() - 1; i > 0; i--) {
            shownUpper[i] = shownUpper[i - 1];
            shownLower[i] = shownLower[i - 1];
        }//�滻�ʣ�����һ��

        offset = (offset + 1) % 2;//offset��0��1֮��任������ʵ��ÿ���غϼ���һ�����ʵ��趨
        if (offset) {
            shownUpper[0] = upper[cur];
            shownLower[0] = lower[cur];
            cur++;
        }
        for (int i = offset; i < shownUpper.size(); i += 2) {//���ظ������bug�����԰�Ӧ���ǰװ�ĵط��������˰װ�
            shownUpper[i] = blank;
            shownLower[i] = blank;
        }
        for (int i = 0; i < shownUpper.size(); i++) {
            PosControl::setPos(i + 1, 1);
            shownUpper[i].putWord();
            PosControl::setPos(i + 22, 1);
            shownLower[i].putWord();
        }//���һ�鵱ǰ��shown
        typeAndColor(shownUpper, shownLower, player);//���ĺ������жϴ����õ�

        cls();//��д��������ֻ����ֵ�����
        PosControl::setPos(17, 0);
        player.getBackpack().printItemList(1);
        showHP(player);//չʾѪ��
        if (monster.getCurrHP() <= 0 || player.getCurrHP() <= 0)
            return;//�����ж�
    }
    while (1) {//����������while��ʵ��ֻ࣬�ǲ��������µĴʣ����ǰ��Ѿ�������Ĵ����ꡣ
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
    int t = 100;//hjr�����֣�ͨ����ζ��ݵ�sleep��һ��ˢ����϶���ܴ�����ĸ
    char next = ' ';//next����һ�������õ��ַ�
    int itemClock[10] = {0};
    while (t-- >= 0) {
        Sleep(5);
        next = ' ';
        if (_kbhit()) {//get�����ַ�
            next = _getch();
        }
        if (next <= 'z' && next >= 'a') {//Сд��ĸ����Ӧ����
            bool existWrong = 0, existUnfinished = 0;//����״̬��������ѭ�����Ƿ���ڴ���Ƿ���ڴ���һ��Ĵ�
            for (int i = lower.size() - 1; i >= 0; i--) {//δ������־��������ԣ�������ѭ��һ������û��δ�����
                int cur = lower[i].getCur();//�����cur�Ǵʵ�״̬����ʾ��ǰ���˼����ַ���ͨ��Ϊ0��
                if (!lower[i].getState() && cur != 0) {//�����һ����û���꣬curҲ����0��˵���ҵ���δ����Ĵ�
                    existUnfinished = 1;//��״̬
                    if (lower[i].getString()[cur] == next) {//�����һλ�ͼ����õ�ƥ��ɹ�
                        lower[i].changeColor(lower[i].getCur(), 5);//Ⱦɫ
                        lower[i].changeCur(cur + 1);//��һλ
                        updatePrint(upper, lower);//���������������ʾ����ɫ
                        int state = deeper(t, lower[i], upper, lower);//����deeper���Ե�ǰ���ʽ��н�һ��ƥ�䣬������״̬
                        if (state == -1) {//deeper����ʱ�������
                            existWrong = 1;//���ڴ���
                            existUnfinished = 0;//����˻ص����ǰ�����Բ�����û����ɵĴ���
                            break;
                        } else if (state == 0 && lower[i].getCur() == lower[i].getLength()) {//д����
                            lower[i].changeState(1);//��������
                            updatePrint(upper, lower);//genshin
                            existUnfinished = 0;//������û��ɵĴ���
                            monster.getDamaged(lower[i].getEffect());//���������Ӧ��д����
                            break;
                            //��дeffects ������effectsҲ�ĺ���
                        } else {
                            //������ɶҲ���ø�
                        }
                    } else {//û��deeper��ֱ�Ӵ������
                        for (int j = 0; j < lower[i].getCur(); j++) {//����ͬ��
                            lower[i].changeColor(j, 8);
                        }
                        lower[i].changeCur(0);
                        updatePrint(upper, lower);
                        existWrong = 1;
                        existUnfinished = 0;
                        break;
                    }
                }
                if (existUnfinished)break;//�������û����Ĵʣ��������ˣ���Ȼ�����ͬʱ�ж��δ����Ĵʵ������
            }
            for (int i = lower.size() - 1; i >= 0; i--) {//���������Ĵʵ��жϡ�
                if (existWrong || existUnfinished)break;//������Ҳ���д���û��������������ѭ����ҲҪд��
                if (!lower[i].getState() && next == lower[i].getString()[0] && !lower[i].getCur()) {//�������
                    lower[i].changeColor(0, 5);
                    lower[i].changeCur(1);
                    updatePrint(upper, lower);
                    int state = deeper(t, lower[i], upper, lower);
                    if (state == -1) {
                        break;
                    } else if (state == 0 && lower[i].getCur() == lower[i].getLength()) {
                        lower[i].changeState(1);
                        updatePrint(upper, lower);
                        monster.getDamaged(lower[i].getEffect()); //��֪����������ʲô�����һ���˳�ָĵĺ�236һ����
                        break;
                        //��дeffects
                    } else {
                        existUnfinished = 1;
                    }
                }
            }
        } else if (next <= 'Z' && next >= 'A') {//��Сд������
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
                        if (state == -1) {//deeper����ʱ�������
                            existWrong = 1;
                            existUnfinished = 0;
                            break;
                        } else if (state == 0 && upper[i].getCur() == upper[i].getLength()) {
                            upper[i].changeState(1);
                            updatePrint(upper, lower);
                            existUnfinished = 0;
                            break;
                            //��дeffects
                        } else {
                            //������ɶҲ���ø�
                        }
                    } else {//û��deeper��ֱ�Ӵ������
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
                        //��дeffects
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
    // �������
    for (int i = 0; i < 4; i++) {
        cout << "\33[2K" << endl;
    }
    PosControl::setPos(17, 0);
    backpack.printItemList(1);
}

void FightScene::showTutorial() {
    std::cout << "�̳�" << std::endl;
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
    while (t-- >= 0) {//�̳б�ʾ������t��ȷ��ÿ������ʱ���ͳһ��
        char next = ' ';//��������һ����Ҳ���������
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
