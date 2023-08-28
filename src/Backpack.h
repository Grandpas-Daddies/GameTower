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
    void showItemList();
private:
    std::vector<std::pair<Item,int>> items;

};

void Backpack::showItemList() {
    for (auto &item : items) {
        std::cout << item.first.getName() << " " << item.second << std::endl;
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

}


#endif //GAMETOWER1_BACKPACK_H
