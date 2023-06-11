#include "../headers/cells.hpp"

// Cell class implementation
Cell::Cell() : type_(CellType::WALL) {}

// Cell class methods

// Set the type of the cell
void Cell::setType(CellType type)
{
    type_ = type;
}

// Get the type of the cell
CellType Cell::getType() const
{
    return type_;
}
