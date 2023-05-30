#include "../headers/maze.hpp"
#include <iostream>

Maze::Maze() : width_(10), height_(10) {
    initializeCells();
}

Maze::Maze(int width, int height) : width_(width), height_(height) {
    initializeCells();
}

Maze::~Maze() {
    // TODO implement destructor
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
    // TODO implement recursive backtracker
}

void Maze::print() {
    for (int i = 0; i < width_; i++) {
        for (int j = 0; j < height_; j++) {
            if (cells_[i][j].isWall()) {
                std::cout << "⬜";
            } else {
                std::cout << "⬛";
            }
        }
        std::cout << std::endl;
    }
}