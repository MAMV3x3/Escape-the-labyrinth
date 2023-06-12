#include "../headers/game.hpp"
#include "../headers/screen.hpp"
#include <Windows.h>
#include <algorithm>
#include <iostream>

// Game class constructor

// Default constructor
Game::Game() : width_(11), height_(11), maze_(width_, height_), player_(1, 1), screen_(std::max(width_ * 2, 50), std::max(height_ + 6, 20)) {}

// Constructor with width and height parameters
Game::Game(int width, int height) : width_(width), height_(height), maze_(width_, height_), player_(1, 1), screen_(std::max(width_ * 2, 50), std::max(height_ + 6, 20))
{
    if (width < 3)
    {
        width_ = 3;
    }
    if (height < 3)
    {
        height_ = 3;
    }
    if (width_ % 2 == 0)
    {
        width_++;
    }
    if (height_ % 2 == 0)
    {
        height_++;
    }
    maze_.setWidth(width_);
    maze_.setHeight(height_);
    screen_.resizeConsoleWindow(std::max(width_ * 2, 50), std::max(height_ + 6, 20));
}

// Game class methods

// Main menu
void Game::init()
{
    screen_.resizeConsoleWindow(screen_.getWidth(), screen_.getHeight());
    screen_.setConsoleTitle();
    screen_.hideCursor();
    screen_.clear();
    player_.setLives(3);
    player_.setScore(0);
    screen_.drawMenu();
    int option = 0;
    std::cin >> option;
    switch (option)
    {
    case 1:
        screen_.clear();
        run();
        break;
    case 2:
        exit(0);
        break;
    default:
        exit(0);
        break;
    }
}

// Main game loop
void Game::run()
{
    maze_.generate();
    player_.setX(maze_.getStartX());
    player_.setY(maze_.getStartY() - 1);
    maze_.setCellType(player_.getX(), player_.getY(), CellType::PLAYER);
    screen_.clear();
    // Prevent player from moving before maze is generated
    Sleep(100);
    while (true)
    {
        if (checkGameStatus() == 0)
        {
            gameOver();
            break;
        }
        else if (checkGameStatus() == 1)
        {
            update();
        }
        handleInput();
        render();
        Sleep(100);
    }
}

// Handle player inputs and update player position
void Game::handleInput()
{
    if (GetAsyncKeyState(VK_UP) )
    {
        checkCollision(0);
        player_.handleMovement(maze_, 0);
    }
    else if (GetAsyncKeyState(VK_RIGHT) )
    {
        checkCollision(1);
        player_.handleMovement(maze_, 1);
    }
    else if (GetAsyncKeyState(VK_DOWN) )
    {
        checkCollision(2);
        player_.handleMovement(maze_, 2);
    }
    else if (GetAsyncKeyState(VK_LEFT) )
    {
        checkCollision(3);
        player_.handleMovement(maze_, 3);
    }
}

// Update game state
void Game::update()
{
    player_.setLives(3);
    player_.setScore(player_.getScore() + 1);
    run();
}

// Render game state
void Game::render()
{
    screen_.clear();
    screen_.drawMaze(maze_, player_, screen_.getWidth(), screen_.getHeight());
}

// Check if player collides with wall
void Game::checkCollision(int direction)
{
    switch (direction)
    {
    case 0:
        if (maze_.getCellType(player_.getX(), player_.getY() - 1) == CellType::WALL)
        {
            player_.setLives(player_.getLives() - 1);
        }
        break;
    case 1:
        if (maze_.getCellType(player_.getX() + 1, player_.getY()) == CellType::WALL)
        {
            player_.setLives(player_.getLives() - 1);
        }
        break;
    case 2:
        if (maze_.getCellType(player_.getX(), player_.getY() + 1) == CellType::WALL)
        {
            player_.setLives(player_.getLives() - 1);
        }
        break;
    case 3:
        if (maze_.getCellType(player_.getX() - 1, player_.getY()) == CellType::WALL)
        {
            player_.setLives(player_.getLives() - 1);
        }
        break;
    }
}

// Game over screen
void Game::gameOver()
{
    screen_.clear();
    screen_.drawGameOver();
    // Yellow color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "\tSCORE: " << player_.getScore() << std::endl
              << std::endl;
    // Reset color to white
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    std::cout << "\t1. Play again" << std::endl;
    std::cout << "\t2. Exit" << std::endl;
    std::cout << "\t>>: ";

    int option = 0;
    std::cin >> option;
    switch (option)
    {
    case 1:
        screen_.clear();
        init();
        break;
    case 2:
        exit(0);
        break;
    default:
        exit(0);
        break;
    }
}

// Check game status
int Game::checkGameStatus()
{
    if (player_.getLives() == 0)
    {
        return 0;
    }
    else if (player_.getX() == maze_.getEndX() && player_.getY() == maze_.getEndY())
    {
        return 1;
    }
    return 2;
}