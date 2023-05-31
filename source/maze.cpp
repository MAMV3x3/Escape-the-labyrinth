#include "../headers/maze.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include "../headers/screen.hpp"

Maze::Maze(int width, int height) : width_(width), height_(height), cells_(width * height) {}

void Maze::generate() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(1, 2);

    int startX = dist(rng) * 2 - 1;
    int startY = 0;
    int endX = dist(rng) * 2 - 1;
    int endY = height_ - 1;

    cells_[startY * width_ + startX].setType(CellType::START);
    cells_[endY * width_ + endX].setType(CellType::END);

    createPath(startX, startY);

    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            int index = y * width_ + x;
            if (cells_[index].getType() == CellType::WALL) {
                std::cout << "⬛";
            } else if (cells_[index].getType() == CellType::PATH) {
                std::cout << "⬜";
            } else if (cells_[index].getType() == CellType::START) {
                std::cout << "🏁";
            } else if (cells_[index].getType() == CellType::END) {
                std::cout << "🚀";
            }
        }
        std::cout << '\n';
    }
}

void Maze::createPath(int x, int y) {
    cells_[y * width_ + x].setType(CellType::PATH);

    while (true) {
        std::vector<std::pair<int, int>> directions;
        if (x >= 2 && cells_[y * width_ + x - 2].getType() == CellType::WALL) {
            directions.emplace_back(-2, 0);
        }
        if (x <= width_ - 3 && cells_[y * width_ + x + 2].getType() == CellType::WALL) {
            directions.emplace_back(2, 0);
        }
        if (y >= 2 && cells_[(y - 2) * width_ + x].getType() == CellType::WALL) {
            directions.emplace_back(0, -2);
        }
        if (y <= height_ - 3 && cells_[(y + 2) * width_ + x].getType() == CellType::WALL) {
            directions.emplace_back(0, 2);
        }

        if (directions.empty()) {
            return;
        }

        std::random_shuffle(directions.begin(), directions.end());
        int dx = directions.back().first;
        int dy = directions.back().second;
        directions.pop_back();

        cells_[(y + dy / 2) * width_ + (x + dx / 2)].setType(CellType::PATH);
        createPath(x + dx, y + dy);
    }
}
