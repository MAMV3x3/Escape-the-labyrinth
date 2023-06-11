#include "../headers/screen.hpp"
#include <iostream>
#include <windows.h>

Screen::Screen(int width, int height) : width_(width), height_(height) {}

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
    // clear whole console
    system("clear");
    gotoxy(0, 0);
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
    std::cout << "Score: " << player.getScore();

    gotoxy(consoleWidth - 1, 1);
    std::cout << "Lives: ";
    for (int i = 0; i < player.getLives(); ++i) {
        std::cout << char(207);
    }

    // Draw maze and player in the middle of the console
    for (int y = 0; y < height; ++y) {
        gotoxy(consoleWidth/2 - width/2, 4 + y);
        for (int x = 0; x < width; ++x) {
            if (maze.getCellType(x, y) == CellType::WALL) {
                // print ascii 178
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
    clear();
    gotoxy(0, 0);
    std::cout << R"(   
    ______                                                   
   |  ____|                                                  
   | |__     ___    ___    __ _   _ __     ___               
   |  __|   / __|  / __|  / _` | | '_ \   / _ |              
   | |____  \__ \ | (__  | (_| | | |_) | |  __/              
   |______| |___/  \___|  \__,_| | .__/   \___|              
       | |   | |                 | |                         
       | |_  | |__     ___       |_|                         
       | __| | '_ \   / _ |                                 
       | |_  | | | | |  __/                                  
  _     \__| |_| |_|  \___|          _           _     _     
 | |         | |                    (_)         | |   | |    
 | |   __ _  | |__    _   _   _ __   _   _ __   | |_  | |__  
 | |  / _` | | '_ \  | | | | | '__| | | | '_ \  | __| | '_ | 
 | | | (_| | | |_) | | |_| | | |    | | | | | | | |_  | | | |
 |_|  \__,_| |_.__/   \__, | |_|    |_| |_| |_|  \__| |_| |_|
                       __/ |                                 
                      |___/                                  
    )" << std::endl;
    std::cout << "1. Play" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void Screen::drawGameOver(){
    std::cout << R"(
   _____                                 ____                          _ 
  / ____|                               / __ \                        | |
 | |  __    __ _   _ __ ___     ___    | |  | | __   __   ___   _ __  | |
 | | |_ |  / _` | | '_ ` _ \   / _ \   | |  | | \ \ / /  / _ \ | '__| | |
 | |__| | | (_| | | | | | | | |  __/   | |__| |  \ V /  |  __/ | |    |_|
  \_____|  \__,_| |_| |_| |_|  \___|    \____/    \_/    \___| |_|    (_)                                                    
    )" << '\n';
    std::cout << "Press any key to continue...";
}
