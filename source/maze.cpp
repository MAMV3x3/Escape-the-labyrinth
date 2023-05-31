#include "../headers/maze.hpp"
#include <iostream>
#include <algorithm>

Maze::Maze() : width_(10), height_(10) {
    initializeCells();
}

Maze::Maze(int width, int height) : width_(width), height_(height) {
    initializeCells();
}

Maze::~Maze() {
    // TODO implement destructor
}

const Cell& Maze::getCell(int x, int y) const {
    return cells_[x][y];
}

void Maze::initializeCells() {
    for (int i = 0; i < width_; i++) {
        std::vector<Cell> row;
        for (int j = 0; j < height_; j++) {
            Cell cell(i, j);
            row.push_back(cell);
        }
        cells_.push_back(row);
    }
}

void Maze::generate() {
    generateRecursiveBacktracker(1, 1);
}

void Maze::generateRecursiveBacktracker(int x, int y) {
    // Mark the current cell as visited
    cells_[x][y].setVisited(true);

    // Create a vector of all posible directions to move (up, down, left, right)
    std::vector<std::pair<int, int>> directions = {
        std::make_pair(0, -2),
        std::make_pair(0, 2),
        std::make_pair(-2, 0),
        std::make_pair(2, 0)
    };

    // Shuffle the vector of directions
    std::random_shuffle(directions.begin(), directions.end());

    // For each direction in the vector
    for (const auto& direction : directions) {
        // Get the coordinates of the cell in that direction
        int nextX = x + direction.first;
        int nextY = y + direction.second;

        // If the cell is within the bounds of the maze
        if (nextX >= 0 && nextX < width_ && nextY >= 0 && nextY < height_) {
            // If the cell has not been visited
            if (!cells_[nextX][nextY].isVisited()) {
                // Remove the wall between the current cell and the next cell
                int wallX = (x + nextX) / 2;
                int wallY = (y + nextY) / 2;
                cells_[wallX][wallY].setWall(false);

                // Recursively call the function with the next cell
                generateRecursiveBacktracker(nextX, nextY);
            }
        }
    }
}

int Maze::getWidth() const {
    return width_;
}

int Maze::getHeight() const {
    return height_;
}