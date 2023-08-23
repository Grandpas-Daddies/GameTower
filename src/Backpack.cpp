//
// Created by xiao on 2023-08-22.
//

#include "Backpack.h"

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
