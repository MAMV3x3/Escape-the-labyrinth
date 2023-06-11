#include "../headers/game.hpp"
#include "../headers/screen.hpp"
#include <Windows.h>
#include <algorithm>
#include <iostream>

Game::Game() : width_(11), height_(11), maze_(width_, height_), player_(1, 1), screen_(std::max(width_ * 2, 50), std::max(height_ + 6, 20)){}

Game::Game(int width, int height) : width_(width), height_(height), maze_(width_, height_), player_(1, 1), screen_(std::max(width * 2, 50), std::max(height + 6, 20)) {}

void Game::init() {
    screen_.resizeConsoleWindow(screen_.getWidth(), screen_.getHeight());
    screen_.setConsoleTitle();
    screen_.clear();
    screen_.drawMenu();
    player_.setLives(3);
    player_.setScore(0);
    int option = 0;
    std::cin >> option;
    switch (option) {
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

void Game::run() {
    maze_.generate();
    player_.setX(maze_.getStartX());
    player_.setY(maze_.getStartY() - 1);
    maze_.setCellType(player_.getX(), player_.getY(), CellType::PLAYER);
    screen_.clear();
    while (true) {
        if(checkGameStatus() == 0) {
            gameOver();
            break;
        } else if (checkGameStatus() == 1) {
            update();
        }
        handleInput();
        render();
        Sleep(100);
    }
}

void Game::handleInput() {
    if (GetAsyncKeyState(VK_UP) & 0x8000) { 
        checkCollision(0);
        player_.handleMovement(maze_, 0);
    } else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        checkCollision(1);
        player_.handleMovement(maze_, 1);
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        checkCollision(2);
        player_.handleMovement(maze_, 2);
    } else if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        checkCollision(3);
        player_.handleMovement(maze_, 3);
    }
}

void Game::update() {
    player_.setLives(3);
    player_.setScore(player_.getScore() + 1);
    run();
}

void Game::render() {
    screen_.clear();
    //screen_.drawWindowBorder();
    screen_.drawMaze(maze_, player_, screen_.getWidth(), screen_.getHeight());
}

void Game::checkCollision(int direction) {
    switch (direction) {
        case 0:
            if (maze_.getCellType(player_.getX(), player_.getY() - 1) == CellType::WALL) {
                player_.setLives(player_.getLives() - 1);
            }
            break;
        case 1:
            if (maze_.getCellType(player_.getX() + 1, player_.getY()) == CellType::WALL) {
                player_.setLives(player_.getLives() - 1);
            }
            break;
        case 2:
            if (maze_.getCellType(player_.getX(), player_.getY() + 1) == CellType::WALL) {
                player_.setLives(player_.getLives() - 1);
            }
            break;
        case 3:
            if (maze_.getCellType(player_.getX() - 1, player_.getY()) == CellType::WALL) {
                player_.setLives(player_.getLives() - 1);
            }
            break;
    }
}

void Game::gameOver() {
    screen_.clear();
    screen_.drawGameOver();
    std::cin.clear();
    std::cout << "\tSCORE: " << player_.getScore() << std::endl << std::endl;
    std::cout << "\t1. Play again" << std::endl;
    std::cout << "\t2. Exit" << std::endl;
    std::cout << "\t>>: ";
    int option = 0;
    std::cin >> option;
    switch (option) {
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

int Game::checkGameStatus() {
    if (player_.getLives() == 0) {
        return 0;
    } else if (player_.getX() == maze_.getEndX() && player_.getY() == maze_.getEndY()) {
        return 1;
    }
    return 2;
}