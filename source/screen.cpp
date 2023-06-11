#include "../headers/screen.hpp"
#include <iostream>
#include <algorithm>
#include <windows.h>

Screen::Screen(int width, int height) : width_(width), height_(height) {}

void Screen::gotoxy(int x, int y) {
    short int _x = x;
    short int _y = y;
    COORD coord = {_x, _y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Screen::resizeConsoleWindow(int width, int height) {
    int8_t consoleWidth = width;
    int8_t consoleHeight = height;
    COORD coord = {consoleWidth, consoleHeight};
    SMALL_RECT rmin = {0, 0, 1, 1};
    SMALL_RECT rect = {0, 0, static_cast<int8_t>(width - 1), static_cast<int8_t>(height - 1)};

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(Handle, TRUE, &rmin);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &rect);
}

void Screen::clear() {
    // clear whole console
    gotoxy(0, 0);
    system("cls");
}

void Screen::setConsoleTitle() {
    // const * char is incompatible with LPCWSTR
    // so we need to convert it
    SetConsoleTitleA("Escape the labyrinth");
}

void Screen::drawMaze(const Maze& maze, const Player& player, int screenWidth, int screenHeight) {
    const int width = maze.getWidth();
    const int height = maze.getHeight();
    const int startX = maze.getStartX();
    const int startY = maze.getStartY();

    // Resize console window to fit the UI
    const int consoleWidth = screenWidth;
    const int consoleHeight = screenHeight;

    // // Draw score and lives
    gotoxy(2, 2);
    std::cout << "Score: " << player.getScore();

    gotoxy(consoleWidth/2 + width/3, 2);
    std::cout << "Lives: ";
    for (int i = 0; i < player.getLives(); ++i) {
        std::cout << char(207);
    }

    // Draw maze and player in the middle of the console
    for (int y = 0; y < height; ++y) {
        gotoxy(consoleWidth/2 - width/2, 4 + y);
        for (int x = 0; x < width; ++x) {
            if (maze.getCellType(x, y) == CellType::WALL) {
                std::cout << char(219);
            } else if ((maze.getCellType(x, y) == CellType::PATH) || (maze.getCellType(x, y) == CellType::START)) {
                std::cout << " ";
            } else if (maze.getCellType(x, y) == CellType::END) {
                std::cout << char(206);
            } else if (maze.getCellType(x, y) == CellType::PLAYER) {
                std::cout << char(207);
            }
        }
        std::cout << '\n';
    }
}

int Screen::getHeight() const {
    return height_;
}

int Screen::getWidth() const {
    return width_;
}

void Screen::setHeight(int height) {
    height_ = height;
}

void Screen::setWidth(int width) {
    width_ = width;
}

void Screen::drawMenu() {
    gotoxy(1, 1);
    std::cout << R"(   
     _____                           
    |   __|___ ___ ___ ___ ___       
    |   __|_ -|  _| .'| . | -_|      
    |_____|___|___|__,|  _|___|      
    | |_| |_ ___      |_|            
    |  _|   | -_|                    
    |_| |_|_|___|      _     _   _   
    | |___| |_ _ _ ___|_|___| |_| |_ 
    | | .'| . | | |  _| |   |  _|   |
    |_|__,|___|_  |_| |_|_|_|_| |_|_|
              |___|                         
    )" << std::endl;
    std::cout << "\t1. Play" << std::endl;
    std::cout << "\t2. Exit" << std::endl;
    std::cout << "\t>>: ";
}

void Screen::drawGameOver(){
    clear();
    gotoxy(1, 1);
    std::cout << R"(
     _____                
    |   __|___ _____ ___  
    |  |  | .'|     | -_| 
    |_____|__,|_|_|_|____ 
    _____             |  |
    |     |_ _ ___ ___|  |
    |  |  | | | -_|  _|__|
    |_____|\_/|___|_| |__|                                                  
    )" << '\n';
}
