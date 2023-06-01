#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "../headers/maze.hpp"

class Screen {
public:
    static void clear();
    static void drawMaze(const Maze& maze);
};

#endif  // SCREEN_HPP
