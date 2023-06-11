#ifndef CELLS_HPP
#define CELLS_HPP

enum class CellType
{
    WALL,
    PATH,
    START,
    END,
    PLAYER
};

class Cell
{
public:
    Cell();

    void setType(CellType type);
    CellType getType() const;

private:
    CellType type_;
};

#endif // CELLS_HPP
