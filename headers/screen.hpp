#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "maze.hpp"

class Screen {
    public:
        Screen();
        Screen(int width, int height);
        ~Screen();

        void displayMaze(const Maze& maze);
        void clearScreen();

    private:
        int width_;
        int height_;
};

#endif // SCREEN_HPP