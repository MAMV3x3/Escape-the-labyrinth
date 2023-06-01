#include "../headers/screen.hpp"
#include <iostream>

void Screen::clear() {
    std::cout << "\033[2J\033[1;1H";
}

void Screen::drawMaze(const Maze& maze) {
    maze.drawMaze();
}