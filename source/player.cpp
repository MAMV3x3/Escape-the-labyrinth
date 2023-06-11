// player.cpp
#include "../headers/player.hpp"

// Set player temporal cordinates, lives and score
Player::Player() : x_(0), y_(0), lives_(3), score_(0) {}

Player::Player(int x, int y) : x_(x), y_(y), lives_(3), score_(0) {}

// Defines all posible movement of the player
void Player::handleMovement(Maze &maze, int direction)
{
    // 0 - up
    // 1 - right
    // 2 - down
    // 3 - left

    switch (direction)
    {
    case 0:
        if (maze.getCellType(x_, y_ - 1) != CellType::WALL)
        {
            maze.setCellType(x_, y_, CellType::PATH);
            maze.setCellType(x_, y_ - 1, CellType::PLAYER);
            y_--;
        }
        break;
    case 1:
        if (maze.getCellType(x_ + 1, y_) != CellType::WALL)
        {
            maze.setCellType(x_, y_, CellType::PATH);
            maze.setCellType(x_ + 1, y_, CellType::PLAYER);
            x_++;
        }
        break;
    case 2:
        if (maze.getCellType(x_, y_ + 1) != CellType::WALL)
        {
            maze.setCellType(x_, y_, CellType::PATH);
            maze.setCellType(x_, y_ + 1, CellType::PLAYER);
            y_++;
        }
        break;
    case 3:
        if (maze.getCellType(x_ - 1, y_) != CellType::WALL)
        {
            maze.setCellType(x_, y_, CellType::PATH);
            maze.setCellType(x_ - 1, y_, CellType::PLAYER);
            x_--;
        }
        break;
    }
}

//Gets all player needed date
int Player::getX() const
{
    return x_;
}

int Player::getY() const
{
    return y_;
}

int Player::getLives() const
{
    return lives_;
}

void Player::setLives(int lives)
{
    lives_ = lives;
}

int Player::getScore() const
{
    return score_;
}

void Player::setScore(int score)
{
    score_ = score;
}

void Player::setX(int x)
{
    x_ = x;
}

void Player::setY(int y)
{
    y_ = y;
}
