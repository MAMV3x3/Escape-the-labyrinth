// player.hpp
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../headers/maze.hpp"

class Player {
public:
    Player(int x, int y);

    void handleMovement(Maze& maze, int direction);

    int getX() const;
    int getY() const;
    int getLives() const;
    int getScore() const;
    void setX(int x);
    void setY(int y);
    void setLives(int lives);
    void setScore(int score);

private:
    int x_;
    int y_;
    int lives_;
    int score_;
};

#endif  // PLAYER_HPP
