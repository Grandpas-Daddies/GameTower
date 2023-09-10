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
    Backpack();
    void addItem(Item item);
    void showItemList(std::ostream &os = std::cout) const;
    void loadItemList(std::istream &is = std::cin);
private:
    std::vector<std::pair<Item,int>> items;

};

void Backpack::showItemList(std::ostream &os) const {
    for (auto &item : items) {
         os << item.first.getName() << " " << item.second << std::endl;
    }
    os << "#" << std::endl;
}

void Backpack::loadItemList(std::istream &is) {
    std::string name;
    int effect;
    int cooldown;
    int num;
    while (is >> name) {
        if (name == "#") {
            return;
        }
        is  >> effect >> cooldown >> num;
        Item item(name, effect, cooldown);
        items.emplace_back(item, num);
    }
}

void Backpack::addItem(Item item) {
    for(auto &i : items) {
        if(i.first.getName() == item.getName()) {
            i.second++;
            return;
        }
    }
    items.emplace_back(item, 1);
}

// ��������е�սǰ׼��Ӫ��ʱ����������ƷaddItem���ɡ���Ʒ˵����ʹ��˵����������Background/սǰ׼��Ӫ��.txt���ˡ�
Backpack::Backpack() {
    items.clear();

    // ����3�� MysteriousPotion ��Ʒ��ÿ����Ѫ50����ȴ20��
    for (int i = 0; i < 3; ++i) {
        Item mysteriousPotion("MysteriousPotion", 50, 20);
//        addItem(mysteriousPotion);
    }

    // ����2�� WormVirus.exe ��Ʒ��ÿ���ù����Ѫ80����ȴ30��
    for (int i = 0; i < 2; ++i) {
        Item wormVirus("WormVirus.exe", -80, 30);
//        addItem(wormVirus);
    }
}


#endif //GAMETOWER1_BACKPACK_H
