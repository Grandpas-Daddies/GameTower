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


#endif //GAMETOWER1_BACKPACK_H
