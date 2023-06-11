#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "maze.hpp"
#include "cells.hpp"
#include "player.hpp"

class Screen
{
public:
    Screen();
    Screen(int width, int height);
    static void clear();
    static void drawMaze(const Maze &maze, const Player &player, int screenWidth, int screenHeight);
    static void resizeConsoleWindow(int width, int height);
    void setWidth(int width);
    void setHeight(int height);
    int getWidth() const;
    int getHeight() const;
    void drawMenu();
    void drawGameOver();
    static void setConsoleTitle();
    static void hideCursor();

private:
    int width_;
    int height_;
    int consoleWidth_;
    int consoleHeight_;
    static void gotoxy(int x, int y);
};

#endif // SCREEN_HPP
