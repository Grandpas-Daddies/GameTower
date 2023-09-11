//
// Created by Jiarong on 2023/8/21.
//

//A MUD Game

#define NOMINMAX

#include <iostream>
#include <csignal>
#include "Interface.h"
#include "Data.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;



int main() {
    //setDPI();
    welcomePage();
    int x, y;
    string name;
    cout << "������������֣�";
    PosControl::getPos(x, y);
    cin >> name;
    while (name.length() > 15 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") !=
                                 string::npos) {
        PosControl::setPos(x, 0);
        // �����ǰ��
        cout << "\033[2K";
        // ����Windows�ļ��������õ��ַ����ж�name�Ƿ�Ϸ�
        if (name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") !=
            string::npos) {
            cout << "�����к��зǷ��ַ������������룺";
        } else {
            cout << "���ֹ��������������룺";
        }
        cin >> name;
    }
    PosControl::setPos(x, 0);
    Player player(name);

    // TODO:
    cout << "    ��ã���Ϊ\033[5m " << name << " \033[0m�� Alex Potter��" << endl << "\033[2K" << endl << "\033[2K";
    Menu menu[3]{
            "����Ϸ",
            "������Ϸ",
            "�˳���Ϸ"
    };
    switch (switcher(menu, 3)) {
        case 0:
            newGame(player);
            break;
        case 1:
            loadGame(player);
            break;
        case 2:
            goodbye();
            system("pause");
            return 0;
    }
    return 0;
}
