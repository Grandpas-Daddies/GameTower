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
    PosControl::getPos(x, y);
    PosControl::setPos(x, 0);
    cout << "\33[2K";
    cout << "������������֣�";
    cin >> name;
    while (name.length() > 15 || name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_") !=
                                 string::npos) {
        PosControl::setPos(x, 0);
        // �����ǰ��
        cout << "\33[2K" << endl;
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

    cout << "    ��ã���Ϊ ";
    //������Ϊ��ɫ
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
    cout << name ;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << " �� Alex Potter��" << endl;
    // ��ʹ��\33�������ǰ��
    string spaceLine(100, ' ');
    cout << spaceLine << endl << spaceLine << endl;
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
