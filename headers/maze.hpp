#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <random>
#include "../headers/cells.hpp"

class Maze
{
public:
    Maze();
    Maze(int width, int height);

    void generate();
    int getWidth() const;
    int getHeight() const;
    int getStartX() const;
    int getStartY() const;
    int getEndX() const;
    int getEndY() const;
    void setWidth(int width);
    void setHeight(int height);
    void setStartCell(int x, int y);
    void setEndCell(int x, int y);
    CellType getCellType(int x, int y) const;
    void setCellType(int x, int y, CellType type);

private:
    int width_;
    int height_;
    int startX_;
    int startY_;
    int endX_;
    int endY_;
    std::vector<Cell> cells_;

    void createPath(int x, int y);
};

#endif // MAZE_HPP
