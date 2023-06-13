#include "../headers/maze.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include "../headers/screen.hpp"

Maze::Maze() : width_(11), height_(11), cells_(width_ * height_) {}

// Defines Cell Size
Maze::Maze(int width, int height) : width_(width), height_(height), cells_(width * height)
{
    if (width_ % 2 == 0)
    {
        width_ += 1;
    }
    if (height_ % 2 == 0)
    {
        height_ += 1;
    }
    cells_.resize(width_ * height_);
}

void Maze::generate()
{
    // Fill the maze grid with walls
    for (int i = 0; i < width_ * height_; i++)
    {
        cells_[i].setType(CellType::WALL);
    }

    std::random_device rd;
    std::mt19937 rng(rd());

    // We want to select a random spot to start the maze generation in the top border
    std::uniform_int_distribution<int> dist(1, (width_) / 2);

    int startX = dist(rng) * 2 - 1;
    int startY = 1;
    setStartCell(startX, startY);

    createPath(startX, startY);

    cells_[(startY - 1) * width_ + startX].setType(CellType::START);

    // Pick a random cell in the bottom border adyacent to a path cell
    // Finding a potential end cell
    std::vector<int> potentialEndCells;
    for (int x = 1; x < width_ - 1; x += 1)
    {
        int y = height_ - 1;
        if (cells_[(y - 1) * width_ + x].getType() == CellType::PATH)
        {
            potentialEndCells.push_back(y * width_ + x);
        }
    }

    // Randomly select an end cell from the potential end cells
    if (!potentialEndCells.empty())
    {
        int selectedCellIndex = std::rand() % potentialEndCells.size();
        int selectedCell = potentialEndCells[selectedCellIndex];
        setEndCell(selectedCell % width_, selectedCell / width_);
        cells_[selectedCell].setType(CellType::END);
    }
}
// Identifies if the cell is a Wall
CellType Maze::getCellType(int x, int y) const
{
    if (x < 0 || x >= width_ || y < 0 || y >= height_)
    {
        return CellType::WALL; // Return WALL for out-of-bounds coordinates
    }
    return cells_[y * width_ + x].getType();
}

// Defines cell type
void Maze::setCellType(int x, int y, CellType type)
{
    cells_[y * width_ + x].setType(type);
}

// Creates the path of the labyrinth
void Maze::createPath(int x, int y)
{
    cells_[y * width_ + x].setType(CellType::PATH);

    while (true)
    {
        std::vector<std::pair<int, int>> directions;
        if (x >= 2 && cells_[y * width_ + x - 2].getType() == CellType::WALL)
        {
            directions.emplace_back(-2, 0);
        }
        if (x <= width_ - 3 && cells_[y * width_ + x + 2].getType() == CellType::WALL)
        {
            directions.emplace_back(2, 0);
        }
        if (y >= 2 && cells_[(y - 2) * width_ + x].getType() == CellType::WALL)
        {
            directions.emplace_back(0, -2);
        }
        if (y <= height_ - 3 && cells_[(y + 2) * width_ + x].getType() == CellType::WALL)
        {
            directions.emplace_back(0, 2);
        }

        if (directions.empty())
        {
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

// Get all necesary variables
void Maze::setWidth(int width)
{
    width_ = width;
}

void Maze::setHeight(int height)
{
    height_ = height;
}

int Maze::getWidth() const
{
    return width_;
}

int Maze::getHeight() const
{
    return height_;
}

int Maze::getStartX() const
{
    return startX_;
}

int Maze::getStartY() const
{
    return startY_;
}

int Maze::getEndX() const
{
    return endX_;
}

int Maze::getEndY() const
{
    return endY_;
}

void Maze::setStartCell(int x, int y)
{
    startX_ = x;
    startY_ = y;
}

void Maze::setEndCell(int x, int y)
{
    endX_ = x;
    endY_ = y;
}