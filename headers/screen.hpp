#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "maze.hpp"
#include "cells.hpp"
#include "player.hpp"

class Screen {
public:
    static void clear();
    static void drawMaze(const Maze& maze, const Player& player);
    static void resizeConsoleWindow(int width, int height);

private:
    static void gotoxy(int x, int y);
};

#endif  // SCREEN_HPP
