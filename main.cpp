//
// Created by Jiarong on 2023/8/21.
//

//A MUD Game

#include <iostream>
#include <Windows.h>
#include "map.h"

using namespace std;




void FullScreen() {
    HWND hwnd = GetForegroundWindow();
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
//    char setting[30];
//    sprintf_s(setting, "mode con:cols=%d lines=%d", x, y);
//    system(setting);
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, x, y, NULL);
    MoveWindow(hwnd, x/10, y/10, x*4/5, y*3/4, 1);
}

void Welcome() {
    FullScreen();

    // set console color to yellow
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    cout
            << "      ___           ___           ___       ___           ___           ___           ___           ___           ___           ___     "
            << endl
            << "     /  /\\         /  /\\         /  /\\     /  /\\         /  /\\         /  /\\         /  /\\         /  /\\         /  /\\         /  /\\    "
            << endl
            << "    /  /::\\       /  /::\\       /  /:/    /  /::\\       /  /::\\       /  /::\\       /  /::|       /  /::\\       /  /::\\       /  /::\\   "
            << endl
            << "   /  /:/\\:\\     /  /:/\\:\\     /  /:/    /  /:/\\:\\     /  /:/\\:\\     /  /:/\\:\\     /  /:|:|      /  /:/\\:\\     /  /:/\\:\\     /  /:/\\:\\  "
            << endl
            << "  /  /:/  \\:\\   /  /::\\ \\:\\   /  /:/    /  /::\\ \\:\\   /  /::\\ \\:\\   /  /::\\ \\:\\   /  /:/|:|__   /  /:/  \\:\\   /  /::\\ \\:\\   /  /::\\ \\:\\ "
            << endl
            << " /__/:/ \\__\\:| /__/:/\\:\\_\\:\\ /__/:/    /__/:/\\:\\_\\:\\ /__/:/\\:\\_\\:| /__/:/\\:\\ \\:\\ /__/:/ |:| /\\ /__/:/_\\_ \\:\\ /__/:/\\:\\_\\:| /__/:/\\:\\_\\:\\"
            << endl
            << " \\  \\:\\ /  /:/ \\__\\/  \\:\\/:/ \\  \\:\\    \\__\\/  \\:\\/:/ \\  \\:\\ \\:\\/:/ \\  \\:\\ \\:\\_\\/ \\__\\/  |:|/:/ \\  \\:\\__/\\_\\/ \\  \\:\\ \\:\\/:/ \\__\\/  \\:\\/:/"
            << endl
            << "  \\  \\:\\  /:/       \\__\\::/   \\  \\:\\        \\__\\::/   \\  \\:\\_\\::/   \\  \\:\\ \\:\\       |  |:/:/   \\  \\:\\ \\:\\    \\  \\:\\_\\::/       \\__\\::/ "
            << endl
            << "   \\  \\:\\/:/        /  /:/     \\  \\:\\       /  /:/     \\  \\:\\/:/     \\  \\:\\_\\/       |__|::/     \\  \\:\\/:/     \\  \\:\\/:/        /  /:/  "
            << endl
            << "    \\__\\::/        /__/:/       \\  \\:\\     /__/:/       \\__\\::/       \\  \\:\\         /__/:/       \\  \\::/       \\__\\::/        /__/:/   "
            << endl
            << "        ~~         \\__\\/         \\__\\/     \\__\\/            ~~         \\__\\/         \\__\\/         \\__\\/            ~~         \\__\\/   "
            << endl;

    // set console color to white
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "                                                                        一个名为";
    // set console color to yellow
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "《达拉崩吧》";
    // set console color to white
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "的MUD游戏" << endl << endl;
    system("pause");
}

int main() {
    Welcome();
    Map map;
    system("cls");
    map.printPlainMap();
    system("pause");
    return 0;
}