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

// 到剧情进行到战前准备营地时，对两个物品addItem即可。物品说明和使用说明都包含在Background/战前准备营地.txt里了。
Backpack::Backpack() {
    items.clear();

    // 创建3个 MysteriousPotion 物品，每个回血50，冷却20秒
    for (int i = 0; i < 3; ++i) {
        Item mysteriousPotion("MysteriousPotion", 50, 20);
//        addItem(mysteriousPotion);
    }

    // 创建2个 WormVirus.exe 物品，每个让怪物扣血80，冷却30秒
    for (int i = 0; i < 2; ++i) {
        Item wormVirus("WormVirus.exe", -80, 30);
//        addItem(wormVirus);
    }
}


#endif //GAMETOWER1_BACKPACK_H
