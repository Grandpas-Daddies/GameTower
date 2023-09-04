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
    if (items.empty()) {
        os << "0" << std::endl;
    }
}

void Backpack::loadItemList(std::istream &is) {
    std::string name;
    int num;
    while (is >> name >> num) {
        Item item(name);
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

Backpack::Backpack() {
    items.clear();
}


#endif //GAMETOWER1_BACKPACK_H
