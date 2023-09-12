//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_BACKPACK_H
#define GAMETOWER1_BACKPACK_H

#include "Item.h"
#include <vector>
#include <iostream>

class Backpack {
public:
    Backpack() = default;
    ~Backpack() = default;

    void addItem(Item item);

    void showItemList(std::ostream &os = std::cout) const;

    void loadItemList(string name, int effect, int cooldown, int num);

    void printItemList(bool atFightScene);

    std::vector<std::pair<Item, int>> &getItemList();

    int getItemClock(int index);

    bool useItem(int index);

    int getItemEffect(int index);

    void progress0();

    void progress4();

    bool isItemExist(int index);

    void clear() {
        items.clear();
        size = 0;
    }

    //����=�����
    Backpack &operator=(const Backpack &backpack) {
        this->items = backpack.items;
        this->size = backpack.size;
        return *this;
    }

    //����==�����
    bool operator==(const Backpack &backpack) {
        bool isEqual = true;
        if (this->size != backpack.size) return false;
        // ����������������Ʒ�б������һ����Ʒ����ȣ��ͷ���false
        for (int i = 0; i < backpack.items.size(); ++i) {
            if (this->items[i].first.getName() != backpack.items[i].first.getName() ||
                this->items[i].first.getEffect() != backpack.items[i].first.getEffect() ||
                this->items[i].first.getClock() != backpack.items[i].first.getClock() ||
                this->items[i].second != backpack.items[i].second) {
                isEqual = false;
                break;
            }
        }
        return isEqual;
    }

private:
    std::vector<std::pair<Item, int>> items;
    int size;



};

void Backpack::showItemList(std::ostream &os) const {
    for (auto item: items) {
        os << item.first.getName() << " " << item.first.getEffect() << " " << item.first.getCooldown() << " " << item.second << " " << std::endl;
    }
    os << "#" << std::endl;
}

void Backpack::loadItemList(std::string name, int effect, int cooldown, int num) {
    addItem(Item(name, effect, cooldown));
}

void Backpack::printItemList(bool atFightScene) {
    for (int i = 0; i < size; i++) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        std::cout << "\t" << "[" << i << "] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        std::cout << items[i].first.getName() << " ����: " << items[i].second << " ";
        if (!atFightScene) {
            cout << endl << "\t\t";
        }
        if (items[i].first.getEffect() > 0) {
            cout << "��Ѫ" << items[i].first.getEffect() << "����ȴ" << items[i].first.getClock() << "��ʱ���" << endl;
        }
        if (items[i].first.getEffect() < 0) {
            cout << "���" << -items[i].first.getEffect() << "���˺�����ȴ" << items[i].first.getClock() << "��ʱ���"
                 << endl;
        }
    }

}

void Backpack::addItem(Item item) {
    for (auto &i: items) {
        if (i.first.getName() == item.getName()) {
            i.second++;
            return;
        }
    }
    items.emplace_back(item, 1);
    size++;
}

void Backpack::progress0() {
    items.clear();

    for (int i = 0; i < 6; ++i) {
        Item LilHealPotion("LittleHealPotion", 10, 50);
        addItem(LilHealPotion);
    }

    // ����2�� WormVirus.exe ��Ʒ��ÿ���ù����Ѫ80����ȴ30��
    for (int i = 0; i < 5; ++i) {
        Item MagicAttack("MagicAttack", -10, 50);
        addItem(MagicAttack);
    }
}

// ��������е�սǰ׼��Ӫ��ʱ����������ƷaddItem���ɡ���Ʒ˵����ʹ��˵����������Background/սǰ׼��Ӫ��.txt���ˡ�
void Backpack::progress4() {

    // ����3�� MysteriousPotion ��Ʒ��ÿ����Ѫ50����ȴ20��
    for (int i = 0; i < 3; ++i) {
        Item mysteriousPotion("MysteriousPotion", 50, 20);
        addItem(mysteriousPotion);
    }

    // ����2�� WormVirus.exe ��Ʒ��ÿ���ù����Ѫ80����ȴ30��
    for (int i = 0; i < 2; ++i) {
        Item wormVirus("WormVirus.exe", -80, 30);
        addItem(wormVirus);
    }
}

int Backpack::getItemClock(int index) {
    return items[index].first.getClock();
}

bool Backpack::useItem(int index) {
    if (items[index].second) {
        items[index].second--;
        return 0;
    }
    return 1;
}

int Backpack::getItemEffect(int index) {
    return items[index].first.getEffect();
}

bool Backpack::isItemExist(int index) {
    return size > index;
}



#endif //GAMETOWER1_BACKPACK_H
