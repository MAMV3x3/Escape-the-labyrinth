#include "headers/maze.hpp"
#include "headers/screen.hpp"

int main() {
    int width = 15;
    int height = 15;

    Screen::clear();

    Maze maze(width, height);
    maze.generate();

    return 0;
}
