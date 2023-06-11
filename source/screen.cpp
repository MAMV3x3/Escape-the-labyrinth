#include "../headers/screen.hpp"
#include <iostream>
#include <windows.h>

void Screen::gotoxy(int x, int y) {
    short int _x = x;
    short int _y = y;
    COORD coord = {_x, _y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Screen::resizeConsoleWindow(int width, int height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    short int consoleWidth = width;
    short int consoleHeight = height;
    SMALL_RECT windowSize = {0, 0, consoleWidth, consoleHeight};
    SetConsoleWindowInfo(hOut, true, &windowSize);
}

void Screen::clear() {
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void Screen::drawMaze(const Maze& maze, const Player& player) {
    const int width = maze.getWidth();
    const int height = maze.getHeight();
    const int startX = maze.getStartX();
    const int startY = maze.getStartY();

    // Resize console window to fit the UI
    const int consoleWidth = width * 2 + 4;
    const int consoleHeight = height + 4;
    resizeConsoleWindow(consoleWidth, consoleHeight);

    // // Draw score and lives
    gotoxy(1, 1);
    std::cout << "Score: " << player.getX();

    gotoxy(consoleWidth - 1, 1);
    std::cout << "Lives: " << player.getY();

    // Draw maze and player in the middle of the console
    for (int y = 0; y < height; ++y) {
        gotoxy(consoleWidth/2 - width/2, 4 + y);
        for (int x = 0; x < width; ++x) {
            if (maze.getCellType(x, y) == CellType::WALL) {
                std::cout << "#";
            } else if ((maze.getCellType(x, y) == CellType::PATH) || (maze.getCellType(x, y) == CellType::START)) {
                std::cout << " ";
            } else if (maze.getCellType(x, y) == CellType::END) {
                std::cout << "E";
            } else if (maze.getCellType(x, y) == CellType::PLAYER) {
                std::cout << "@";
            }
        }
        std::cout << '\n';
    }
}