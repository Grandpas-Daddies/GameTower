//
// Created by xiao on 2023-08-22.
//

#ifndef GAMETOWER1_ITEM_H
#define GAMETOWER1_ITEM_H

#include <iostream>

class Item {
public:
    Item();
    std::string getName() const;
private:
    std::string name;
};

std::string Item::getName() const {
    return name;
}

Item::Item() {

}


#endif //GAMETOWER1_ITEM_H
