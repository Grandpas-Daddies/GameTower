//
// Created by Jiarong on 2023/8/21.
//

//A MUD Game

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <iostream>
#include <fstream>
#include <limits>
#include "Interface.h"
#include "Init.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;
using namespace PosControl;

void welcome() {
    centerWindow();

    cout << "按下";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    cout << "[Tab]";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "跳过本段..." << endl << endl;
    ifstream welcomeFile("../Assets/.welcome");
    char welcome;
    bool flagTab = false;
    while (welcomeFile.get(welcome)) {
        if (GetAsyncKeyState(VK_TAB)) {
            flagTab = true;
        }
        if (!flagTab) Sleep(50);
        cout << welcome;

    }
    welcomeFile.close();

    cout << "\t\t";
    for (int i = 0; i < 6 * 2; i++) {
        Sleep(100);
        cout << ".";
    }
    cout << endl;

    int x, y;
    getPos(x, y);
    int spaceLength = std::max((size.width / 10 - 88) / 2 + 2, 0);
    string space(spaceLength, ' ');
    while (1) {
        setPos(x, y);
        ifstream logoFile("../Assets/.logo");
        string logo;
        while (getline(logoFile, logo)) {
            int color = rand() % 15 + 1;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            Sleep(50);
            cout << space << logo << endl;
        }
        logoFile.close();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << endl << "按下";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "[回车键]";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << "继续..." << endl;
        if (GetAsyncKeyState(VK_RETURN)) {
            break;
        }
    }
    cin.ignore(1024, '\n');
}

char switcher() {

    cout << endl;
    // set console color to yellow
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t" << "[N] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "新游戏" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t" << "[L] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "加载游戏" << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "\t" << "[Q] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "退出游戏" << endl;

    // switch
    cout << endl;
    cout << "请输入你的选择：";

    int x, y;
    getPos(x, y);
    char choice;
    while (1) {
        setPos(x, y);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cin >> choice;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if (choice == 'N' || choice == 'L' || choice == 'Q') {
            return choice;
        }
        // otherwise, clear the input stream then continue
        cout << "输入错误，请重新输入！";
        system("pause");
        //reset the cursor position and clear the line
        setPos(x, y);
        cout << "                                                                  " << endl
             << "                                                                  ";
    }
}


int main() {
    welcome();
    int x, y;
    switch (switcher()) {
        case 'N':
            newGame();
            break;
        case 'L':
            loadGame();
            break;
        case 'Q':
            return 0;
    }
    system("cls");
    system("pause");
    return 0;
}
