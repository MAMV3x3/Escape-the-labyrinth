#include "../headers/cells.hpp"
#include <iostream>

Cell::Cell() : x_(0), y_(0), wall_(false), visited_(false) {}

Cell::Cell(int x, int y) : x_(x), y_(y), wall_(false), visited_(false) {}

Cell::~Cell() {}

void Cell::setWall(bool wall) {
    wall_ = wall;
}

bool Cell::isWall() const {
    return wall_;
}

void Cell::setVisited(bool visited) {
    visited_ = visited;
}

bool Cell::isVisited() const {
    return visited_;
}