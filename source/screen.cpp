#include "../headers/screen.hpp"
#include <iostream>

Screen::Screen() : width_(10), height_(10) {}

Screen::Screen(int width, int height) : width_(width), height_(height) {}

Screen::~Screen() {}

void Screen::displayMaze(const Maze& maze) {
    for (int i = 0; i < maze.getHeight(); i += 1){
        for (int j = 0; j < maze.getWidth(); j += 1){
            if (maze.getCell(j, i).isWall()){
                std::cout << "⬛";
            } else {
                std::cout << "⬜";
            }
        }
        std::cout << std::endl;
    }
}

void Screen::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}