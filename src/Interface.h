//
// Created by Jiarong on 2023/8/22.
//

#ifndef GAMETOWER_INTERFACE_H
#define GAMETOWER_INTERFACE_H

#include "Word.h"
#include <time.h>
//#include "Monster.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <random>
//#include "utils\\rand.h"

using std::cout, std::cin, std::endl, std::ifstream, std::string;


namespace PosControl {

    int screen_width = GetSystemMetrics(SM_CXSCREEN);
    int screen_height = GetSystemMetrics(SM_CYSCREEN);

    // ´°¿Ú³¤¿í
    struct Size {
        int width;
        int height;
    } size = {1020, 860};

    void centerWindow() {
        HWND hwnd = GetForegroundWindow();
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, size.width, size.height, 1);
        MoveWindow(hwnd, (screen_width - size.width) / 2, (screen_height - size.height) / 2, size.width, size.height,
                   1);
    }

// »Øµ½×ø±êÎ»ÖÃ£¬×ø±êÐèÒª¸ø¶¨
    void setPos(int x, int y) {
        COORD coord{static_cast<SHORT>(y), static_cast<SHORT>(x)};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  //»Øµ½¸ø¶¨µÄ×ø±êÎ»ÖÃ½øÐÐÖØÐÂÊä³ö
    }


// »ñÈ¡µ±Ç°±ê×¼Êä³öÁ÷Î»ÖÃ
    void getPos(int &x, int &y) {
        CONSOLE_SCREEN_BUFFER_INFO b;           // °üº¬¿ØÖÆÌ¨ÆÁÄ»»º³åÇøµÄÐÅÏ¢
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &b);    //  »ñÈ¡±ê×¼Êä³ö¾ä±ú
        y = b.dwCursorPosition.X;
        x = b.dwCursorPosition.Y;
    }


    void HideCursor() {
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible = FALSE;
        cursor.dwSize = sizeof(cursor);
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorInfo(handle, &cursor);
    }
}

struct Menu {
    string name;
};

int randInt(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void printMsg(string msgDir, bool singleLine = false, bool noCD = false) {
    if (!singleLine) {
        cout << "°´ÏÂ ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "[Tab¼ü] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "Ìø¹ý±¾¶Î..." << endl << endl;
    }
    ifstream msgFile(msgDir);
    string msg;
    int x, y;
    if (singleLine) {
        PosControl::getPos(x, y);
    }
    int x1 = x, y1 = y;
    while (getline(msgFile, msg)) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        if (singleLine) {
            PosControl::setPos(x, y);
            for (int i = x; i <= x1; i++) {
                cout << "\33[2K" << endl;
            }
            PosControl::setPos(x, y);
        }
        bool flagTab = false;
        for (char c: msg) {

            if (c == '(') // set color to grey
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            else if (c == ')') {// set color to white
                cout << c;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                continue;
            }
            cout << c;
            if (!flagTab) Sleep(5);
            if (!noCD && kbhit()) {
                char c;
                c = getch();
                if (c == '\t') {
                    flagTab = true;
                }
            }
        }
        if (singleLine) {
            cout << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            system("pause");
        }
        Sleep(100);
        PosControl::getPos(x1, y1);
        cout << endl;
    }
    msgFile.close();
}

void welcomePage() {

    PosControl::centerWindow();
    PosControl::HideCursor();

    printMsg("./Assets/.welcomePage");

    cout << endl << endl;
    for (int i = 0; i < 103; i++) {
        Sleep(5);
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

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << endl << "°´ÏÂ ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "[Enter¼ü] ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout << "¼ÌÐø..." << endl;

        if (kbhit()) {
            char c;
            c = getch();
            if (c == '\r' || c == '\n') {
                PosControl::setPos(x + 7, 0);
                break;
            }
        }
    }
    cout << "======================================================================================================="
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << endl << "    ÇëÊ¹ÓÃ ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "[Ctrl] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "+ ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "¹öÂÖ ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "µ÷Õû¿ØÖÆÌ¨×ÖÌå´óÐ¡£¬È·±£ÒÔÉÏ·Ö¸îÏßÏÔÊ¾ÔÚÍ¬Ò»ÐÐ¡£"
         << endl;
    cout << endl << "°´ÏÂ ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "[Enter¼ü] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "¼ÌÐø..." << endl;
    while (1) {
        if (kbhit()) {
            char c;
            c = getch();
            if (c == '\r' || c == '\n') {
                PosControl::setPos(x + 8, 0);
                cout << "                                                                                        "
                     << endl;
                cout << "                                                                                        "
                     << endl;
                cout << "                                                                                        "
                     << endl;
                cout << "                                                                                        "
                     << endl;
                PosControl::setPos(x + 9, 0);
                break;
            }
        }
    }
}

int switcher(Menu menu[], int length) {

    int x, y;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Ê¹ÓÃ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << " [W] [S] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "»ò";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << " [¡ü] [¡ý] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "Ñ¡Ôñ£¬°´";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << " [Enter¼ü] ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "È·ÈÏ" << endl << endl;

    PosControl::getPos(x, y);
    PosControl::setPos(x, 0);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

    for (int i = 0; i < length; i++) {
        cout << "    > " << menu[i].name << endl;
    }
    cout << endl;
    cout << "======================================================================================================="
         << endl;

    char c;
    int choice = 0;
    int prevChoice = 0;

    while (1) {

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        PosControl::setPos(x + prevChoice, y);
        cout << "    > " << menu[prevChoice].name;

        PosControl::setPos(x + choice, y);
        // [43;37mÊÇ»Æµ×°××Ö

        cout << "    ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
                                                                 FOREGROUND_GREEN | FOREGROUND_BLUE |
                                                                 BACKGROUND_RED | BACKGROUND_GREEN);
        cout << "> " << menu[choice].name;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        c = getch();
        switch (c) {
            case 'w':
            case 'W':
            case 72: // 72ÊÇÉÏ¼ýÍ·
                prevChoice = choice;
                choice = (choice + length - 1) % length;
                break;
            case 's':
            case 'S':
            case 80: // 80ÊÇÏÂ¼ýÍ·
                prevChoice = choice;
                choice = (choice + 1) % length;
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

void goodbye() {
    system("cls");
    ifstream creditsLogoFile("./Assets/.credit_logo");
    string logo;
    while (getline(creditsLogoFile, logo)) {
        cout << logo << endl;
        Sleep(randInt(20, 50));
    }
    creditsLogoFile.close();
    ifstream creditsFile("./Assets/.credit");
    string credits;
    while (getline(creditsFile, credits)) {
        cout << credits << endl;
        Sleep(randInt(20, 50));
    }
    creditsFile.close();
}


#endif //GAMETOWER_INTERFACE_H
