// game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include "../headers/maze.hpp"
#include "../headers/player.hpp"
#include "../headers/screen.hpp"

class Game
{
public:
    Game();
    Game(int width, int height);

    void init();

private:
    int width_;
    int height_;
    Maze maze_;
    Player player_;
    Screen screen_;

    void handleInput();
    void update();
    void render();
    void checkCollision(int direction);
    void gameOver();
    void run();
    void nextLevelSound();
    int checkGameStatus();
};

#endif // GAME_HPP
