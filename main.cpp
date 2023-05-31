#include "headers/maze.hpp"
#include "headers/screen.hpp"

int main(){
    Maze maze(20, 20);
    maze.generate();

    Screen screen(40, 40);
    screen.displayMaze(maze);

    return 0;
}