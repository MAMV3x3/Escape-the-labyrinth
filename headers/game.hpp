// game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include "../headers/maze.hpp"
#include "../headers/player.hpp"
#include "../headers/screen.hpp"

class Game : public Screen
{
public:
    Game();
    Game(int width, int height);
    // Game constructor overload with char parameters for each cell type
    Game(int width, int height, char path, char wall, char exit, char playerChar);

    void init();

private:
    int width_;
    int height_;
    Maze maze_;
    Player player_;
    Screen screen_;
    char path_;
    char wall_;
    char exit_;
    char playerChar_;

    void handleInput();
    void update();
    void render();
    void checkCollision(int direction);
    void gameOver();
    void run();
    void nextLevelSound();
    int checkGameStatus();
    bool checkMazeConstructorParameters();
};

#endif // GAME_HPP
