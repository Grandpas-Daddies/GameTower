//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_INTERFACE_H
#define GAMETOWER_INTERFACE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
//#include <limits.h>
#include "src/utils/rand.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;

namespace PosControl {

    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    // 窗口长宽
    struct Size {
        int width;
        int height;
    } size = {1024, 768};

    void centerWindow() {
        HWND hwnd = GetForegroundWindow();
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, size.width, size.height, 1);
        MoveWindow(hwnd, (screen_width - size.width) / 2, (screen_height - size.height) / 2, size.width, size.height,
                   1);
    }

// 回到坐标位置，坐标需要给定
    void setPos(int x, int y) {
        COORD coord{static_cast<SHORT>(y), static_cast<SHORT>(x)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  //回到给定的坐标位置进行重新输出
    }


// 获取当前标准输出流位置
    void getPos(int &x, int &y) {
        CONSOLE_SCREEN_BUFFER_INFO b;           // 包含控制台屏幕缓冲区的信息
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &b);    //  获取标准输出句柄
        y = b.dwCursorPosition.X;
        x = b.dwCursorPosition.Y;
    }

}

struct Menu {
    string name;
};

void clearInputBuffer() {
    cin.clear(); // 清除错误标志
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略剩余的字符，直到遇到换行符
}

void welcome() {
    PosControl::centerWindow();

    cout << "按下 \033[31m[Tab键] \033[0m跳过本段..." << endl << endl;
    ifstream welcomeFile("./Assets/.welcome");
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

    cout << endl << endl;
    for (int i = 0; i < 104; i++) {
        Sleep(10);
        cout << "=";
    }
    cout << endl << endl;

    int x, y;
    PosControl::getPos(x, y);
    int spaceLength = std::max((PosControl::size.width / 10 - 88) / 2 + 2, 0);
    string space(spaceLength, ' ');
    while (1) {
        PosControl::setPos(x, y);
        ifstream logoFile("./Assets/.logo");
        string logo;
        while (getline(logoFile, logo)) {
            int color = randInt(1, 15);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
            Sleep(50);
            cout << space << logo << endl;
        }
        logoFile.close();

        cout << endl << "\033[0m按下 \033[31m[空格键] \033[0m继续..." << endl;

        if (GetAsyncKeyState(VK_SPACE)) {
            PosControl::setPos(x+7, 0);
            return;
        }
        else {
            // TODO: Fix this bug
        }
    }
}

int switcher() {

    Menu menu[3]{
            "新游戏",
            "加载游戏",
            "退出游戏"
    };

    cout << "========================================================================================================" << endl;
    cout << endl;
    int x, y;
    PosControl::getPos(x, y);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    for (int i = 0; i < 3; i++) {
        cout << "    " << menu[i].name << endl;
    }
    cout << endl;
    cout << "========================================================================================================" << endl;

    char c;
    int choice = 0;
    int prevChoice = 0;

    while (1) {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        PosControl::setPos(x + prevChoice, y);
        cout << "    " << menu[prevChoice].name;

        PosControl::setPos(x + choice, y);
        cout << "\33[43;37m" << "    " << menu[choice].name << "\33[0m";
        c = getch();
        switch (c) {
            case 'w':
            case 'W':
            case 72: // 72是上箭头
                prevChoice = choice;
                choice = (choice + 3 - 1) % 3;
                break;
            case 's':
            case 'S':
            case 80: // 80是下箭头
                prevChoice = choice;
                choice = (choice + 1) % 3;
                break;
            case '\r':
            case '\n':
                return choice;
            default:
                prevChoice = choice;
                break;
        }
    }
}

#endif //GAMETOWER_INTERFACE_H
