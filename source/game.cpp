#include "../headers/game.hpp"
#include "../headers/screen.hpp"
#include <Windows.h>
#include <iostream>

Game::Game() : width_(11), height_(11), maze_(width_, height_), player_(1, 1) {}

Game::Game(int width, int height) : width_(width), height_(height), maze_(width_, height_), player_(1, 1) {}

void Game::run() {
    maze_.generate();
    player_.setX(maze_.getStartX());
    player_.setY(maze_.getStartY() - 1);
    maze_.setCellType(player_.getX(), player_.getY(), CellType::PLAYER);
    Screen::clear();
    Screen::resizeConsoleWindow(width_ * 2, height_);

    while (true) {
        if(checkGameStatus() == 0) {
            gameOver();
            break;
        } else if (checkGameStatus() == 1) {
            gameOver();
            break;
        }
        handleInput();
        update();
        render();
        Sleep(100);
    }
}

void Game::handleInput() {
    if (GetAsyncKeyState(VK_UP)) {
        checkCollision(0);
        player_.handleMovement(maze_, 0);
    } else if (GetAsyncKeyState(VK_RIGHT)) {
        checkCollision(1);
        player_.handleMovement(maze_, 1);
    } else if (GetAsyncKeyState(VK_DOWN)) {
        checkCollision(2);
        player_.handleMovement(maze_, 2);
    } else if (GetAsyncKeyState(VK_LEFT)) {
        checkCollision(3);
        player_.handleMovement(maze_, 3);
    }
}

void Game::update() {
    if (maze_.getCellType(player_.getX(), player_.getY()) == CellType::END) {
        // maze_.generate();
        // player_.setLives(3);
        Screen::clear();
        std::cout << "You won!" << std::endl;
    }
}

void Game::render() {
    Screen::clear();
    Screen::drawMaze(maze_, player_);
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

    

    if (player_.getLives() == 0) {
        gameOver();
    }
}

void Game::gameOver() {
    Screen::clear();
    std::cout << "Game over!" << std::endl;
}

int Game::checkGameStatus() {
    if (player_.getLives() == 0) {
        return 0;
    } else if (player_.getX() == maze_.getEndX() && player_.getY() == maze_.getEndY()) {
        return 1;
    }
    return 2;
}