#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <random>
#include "../headers/cells.hpp"

class Maze {
public:
    Maze(int width, int height);

    void generate();
    void drawMaze() const;

private:
    int width_;
    int height_;
    std::vector<Cell> cells_;
    
    void createPath(int x, int y);
};

#endif  // MAZE_HPP
