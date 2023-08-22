//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_INIT_H
#define GAMETOWER_INIT_H

#include <iostream>
#include <fstream>

bool checkProfileExist() {
    std::ifstream fin("profile.dat");
    if (fin) {
        return true;
    } else {
        return false;
    }

}

void init() {
    if (checkProfileExist()) {
        std::cout << "检测到存档，是否读取存档？(Y/N)" << std::endl;
        char choice;
        std::cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            // 读取存档
        } else {
            std::cout << "正在创建新存档..." << std::endl;
            std::ofstream fout("profile.dat");
            fout << time(NULL) << std::endl;

        }
    }
}


#endif //GAMETOWER_INIT_H
