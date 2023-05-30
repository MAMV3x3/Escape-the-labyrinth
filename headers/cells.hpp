#ifndef CELLS_HPP
#define CELLS_HPP

class Cell{
    public:
        Cell();
        Cell(int x, int y);
        ~Cell();

        void setWall(bool wall);
        bool isWall() const;
        void setVisited(bool visited);
        bool isVisited() const;

    private:
        int x_;
        int y_;
        bool wall_;
        bool visited_;
};

#endif // CELLS_HPP