#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include "cells.hpp"

class Maze {
    public:
        Maze();
        Maze(int width, int height);
        ~Maze();

        const Cell& getCell(int x, int y) const;

        void generate();
        int getWidth() const;
        int getHeight() const;

    private:
        int width_;
        int height_;
        std::vector<std::vector<Cell>> cells_;

        void initializeCells();
        void generateRecursiveBacktracker(int x, int y);

};

#endif // MAZE_HPP