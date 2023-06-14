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

// Constructor overload with char parameters for each cell type
Game::Game(int width, int height, char path, char wall, char exit, char playerChar) : width_(width), height_(height), maze_(width_, height_), player_(1, 1), screen_(std::max(width_ * 2, 50), std::max(height_ + 6, 20)), path_(path), wall_(wall), exit_(exit), playerChar_(playerChar)
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
    clear();
    player_.setLives(3);
    player_.setScore(0);
    drawMenu();
    int option = 0;
    std::cin >> option;
    switch (option)
    {
    case 1:
        clear();
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
    clear();
    // Prevent player from moving before maze is generated
    Sleep(200);
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
    if (GetAsyncKeyState(VK_UP))
    {
        checkCollision(0);
        player_.handleMovement(maze_, 0);
    }
    else if (GetAsyncKeyState(VK_RIGHT))
    {
        checkCollision(1);
        player_.handleMovement(maze_, 1);
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        checkCollision(2);
        player_.handleMovement(maze_, 2);
    }
    else if (GetAsyncKeyState(VK_LEFT))
    {
        checkCollision(3);
        player_.handleMovement(maze_, 3);
    }
}

// Update game state
void Game::update()
{
    // Next level sound, winning sound
    nextLevelSound();
    Sleep(1400);
    player_.setLives(3);
    player_.setScore(player_.getScore() + 1);
    run();
}

void Game::nextLevelSound()
{
    Beep(523, 200);
    Beep(587, 200);
    Beep(659, 200);
    Beep(698, 200);
    Beep(784, 200);
    Beep(880, 200);
    Beep(988, 200);
}

// Render game state
void Game::render()
{
    clear();
    if (checkMazeConstructorParameters())
    {
        screen_.drawMaze(maze_, player_, screen_.getWidth(), screen_.getHeight(), path_, wall_, exit_, playerChar_);
    }
    else
    {
        screen_.drawMaze(maze_, player_, screen_.getWidth(), screen_.getHeight());
    }
}

// Check if player collides with wall
void Game::checkCollision(int direction)
{
    switch (direction)
    {
    case 0:
        if (maze_.getCellType(player_.getX(), player_.getY() - 1) == CellType::WALL)
        {
            Beep(523, 100);
            player_.setLives(player_.getLives() - 1);
        }
        break;
    case 1:
        if (maze_.getCellType(player_.getX() + 1, player_.getY()) == CellType::WALL)
        {
            Beep(523, 100);
            player_.setLives(player_.getLives() - 1);
        }
        break;
    case 2:
        if (maze_.getCellType(player_.getX(), player_.getY() + 1) == CellType::WALL)
        {
            Beep(523, 100);
            player_.setLives(player_.getLives() - 1);
        }
        break;
    case 3:
        if (maze_.getCellType(player_.getX() - 1, player_.getY()) == CellType::WALL)
        {
            Beep(523, 100);
            player_.setLives(player_.getLives() - 1);
        }
        break;
    }
}

// Game over screen
void Game::gameOver()
{
    clear();
    drawGameOver();
    // Yellow color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << "\tSCORE: " << player_.getScore() << std::endl
              << std::endl;
    // Reset color to white
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    std::cout << "\t1. Play again" << std::endl;
    std::cout << "\t2. Exit" << std::endl;
    std::cout << "\t>>: ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int option = 0;
    std::cin >> option;
    switch (option)
    {
    case 1:
        clear();
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

bool Game::checkMazeConstructorParameters()
{
    // Check if maze constructor parameters are overloaded
    // If path_ is empty return false [is char* empty?]
    if (path_ != '\0')
    {
        return true;
    }
    return false;
}