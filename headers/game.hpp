// game.hpp
#ifndef GAME_HPP
#define GAME_HPP

#include "../headers/maze.hpp"
#include "../headers/player.hpp"

class Game {
public:
    Game();
    Game(int width, int height);

    void run();

private:
    int width_;
    int height_;
    Maze maze_;
    Player player_;

    void handleInput();
    void update();
    void render();
    void checkCollision(int direction);
    void gameOver();
    int checkGameStatus();
};

#endif  // GAME_HPP
