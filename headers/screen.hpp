#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "maze.hpp"
#include "cells.hpp"
#include "player.hpp"

class Screen {
public:
    Screen(int width, int height);
    static void clear();
    static void drawMaze(const Maze& maze, const Player& player);
    static void resizeConsoleWindow(int width, int height);
    void setWidth(int width);
    void setHeight(int height);
    int getWidth() const;
    int getHeight() const;
    void drawMenu();
    void drawGameOver();

private:
    int width_;
    int height_;
    static void gotoxy(int x, int y);
};

#endif  // SCREEN_HPP
