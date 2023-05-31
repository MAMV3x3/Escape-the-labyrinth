#include "../headers/maze.hpp"

Maze::Maze() : width_(0), height_(0), rng_(rd_()) {}

Maze::Maze(int width, int height) : width_(width), height_(height), rng_(rd_()) {
    initializeGrid();
}

Maze::~Maze() {}

void Maze::initializeGrid() {
    grid_.resize(width_, std::vector<bool>(height_, false));
}

void Maze::generateMaze() {
    // Reset the grid
    initializeGrid();

    // Set the borders as walls
    for (int i = 0; i < width_; ++i) {
        grid_[i][0] = true;                 // Top border
        grid_[i][height_ - 1] = true;       // Bottom border
    }
    for (int j = 0; j < height_; ++j) {
        grid_[0][j] = true;                 // Left border
        grid_[width_ - 1][j] = true;        // Right border
    }

    // Set random start and end positions
    std::uniform_int_distribution<int> dist(1, (width_ - 1) / 2);
    int startX = dist(rng_) * 2;
    int startY = dist(rng_) * 2;
    int endX = dist(rng_) * 2;
    int endY = dist(rng_) * 2;
    grid_[startX][startY] = false;      // Start position
    grid_[endX][endY] = false;          // End position

    // Generate the maze path
    generatePath(startX, startY);
}

void Maze::generatePath(int x, int y) {
    grid_[x][y] = false;

    std::vector<std::pair<int, int>> neighbors = getNeighbors(x, y);
    std::shuffle(neighbors.begin(), neighbors.end(), rng_);

    for (const auto& neighbor : neighbors) {
        int nx = neighbor.first;
        int ny = neighbor.second;
        if (grid_[nx][ny]) {
            int mx = (x + nx) / 2;
            int my = (y + ny) / 2;
            grid_[mx][my] = false;
            generatePath(nx, ny);
        }
    }
}

std::vector<std::pair<int, int>> Maze::getNeighbors(int x, int y) {
    std::vector<std::pair<int, int>> neighbors;

    if (x - 2 >= 0) {
        neighbors.push_back({x - 2, y});
    }
    if (x + 2 < width_) {
        neighbors.push_back({x + 2, y});
    }
    if (y - 2 >= 0) {
        neighbors.push_back({x, y - 2});
    }
    if (y + 2 < height_) {
        neighbors.push_back({x, y + 2});
    }

    return neighbors;
}

void Maze::setPlayerStartPosition(int x, int y) {
    grid_[x][y] = false;
}

void Maze::setExitPosition(int x, int y) {
    grid_[x][y] = false;
}

bool Maze::isWall(int x, int y) const {
    return grid_[x][y];
}

int Maze::getWidth() const {
    return width_;
}

int Maze::getHeight() const {
    return height_;
}
