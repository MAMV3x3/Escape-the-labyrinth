#include "../headers/game.hpp"
#include "../headers/screen.hpp"
#include <Windows.h>
#include <iostream>

Game::Game() : width_(11), height_(11), maze_(width_, height_), player_(1, 1), screen_(11 * 2 + 4, 11 + 4){}

Game::Game(int width, int height) : width_(width), height_(height), maze_(width_, height_), player_(1, 1), screen_(width * 2 + 4, height + 4) {}

void Game::init() {
    screen_.drawMenu();
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
    screen_.resizeConsoleWindow(width_ * 2, height_);

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
    player_.setLives(3);
    player_.setScore(player_.getScore() + 1);
    run();
}

void Game::render() {
    screen_.clear();
    screen_.drawMaze(maze_, player_);
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
    std::cout << "Your score: " << player_.getScore() << std::endl;
    std::cin.get();
    init();
}

int Game::checkGameStatus() {
    if (player_.getLives() == 0) {
        return 0;
    } else if (player_.getX() == maze_.getEndX() && player_.getY() == maze_.getEndY()) {
        return 1;
    }
    return 2;
}