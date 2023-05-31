#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include <random>

class Maze {
public:
    Maze();
    Maze(int width, int height);
    ~Maze();

    void generateMaze();
    void setPlayerStartPosition(int x, int y);
    void setExitPosition(int x, int y);
    bool isWall(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width_;
    int height_;
    std::vector<std::vector<bool>> grid_;
    std::random_device rd_;
    std::mt19937 rng_;

    void initializeGrid();
    std::vector<std::pair<int, int>> getNeighbors(int x, int y);
    void generatePath(int x, int y);
};

#endif