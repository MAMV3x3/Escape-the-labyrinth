#include "../headers/cells.hpp"

Cell::Cell() : type_(CellType::WALL) {}

void Cell::setType(CellType type) {
    type_ = type;
}

CellType Cell::getType() const {
    return type_;
}
