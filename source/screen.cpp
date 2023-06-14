#include "../headers/screen.hpp"
#include <iostream>
#include <algorithm>
#include <Windows.h>

// Screen class constructor

// Default constructor
Screen::Screen() : width_(11), height_(11) {}

// Constructor with width and height parameters
Screen::Screen(int width, int height) : width_(width), height_(height) {}

// Creates console cursor
void Screen::gotoxy(int x, int y)
{
    short int _x = x;
    short int _y = y;
    COORD coord = {_x, _y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Changes size of the console
void Screen::resizeConsoleWindow(int width, int height)
{
    int8_t consoleWidth = width;
    int8_t consoleHeight = height;
    COORD coord = {consoleWidth, consoleHeight};
    SMALL_RECT rmin = {0, 0, 1, 1};
    SMALL_RECT rect = {0, 0, static_cast<int8_t>(width - 1), static_cast<int8_t>(height - 1)};

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(Handle, TRUE, &rmin);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &rect);
}

void Screen::clear()
{
    // Clear whole console
    gotoxy(0, 0);
    system("cls");
}

void Screen::setConsoleTitle()
{
    SetConsoleTitleA("Escape the labyrinth");
}

// Hides console cursor
void Screen::hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Sets UI for the running game
void Screen::drawMaze(const Maze &maze, const Player &player, int screenWidth, int screenHeight)
{
    const int width = maze.getWidth();
    const int height = maze.getHeight();
    const int startX = maze.getStartX();
    const int startY = maze.getStartY();

    // Resize console window to fit the UI
    const int consoleWidth = screenWidth;
    const int consoleHeight = screenHeight;

    // Draw score and lives
    gotoxy(2, 2);
    // Light blue color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    std::cout << "Score: ";
    // Light yellow color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << player.getScore();

    gotoxy(consoleWidth - 12, 2);
    // Light blue color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    std::cout << "Lives: ";
    for (int i = 0; i < player.getLives(); ++i)
    {
        // Light yellow color
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        std::cout << char(207);
        // Reset color
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    // Draw maze and player in the middle of the console
    for (int y = 0; y < height; ++y)
    {
        gotoxy(consoleWidth / 2 - width / 2, 4 + y);
        for (int x = 0; x < width; ++x)
        {
            if (maze.getCellType(x, y) == CellType::WALL)
            {
                // Light black color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                std::cout << char(219);
                // Reset color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else if ((maze.getCellType(x, y) == CellType::PATH) || (maze.getCellType(x, y) == CellType::START))
            {
                std::cout << " ";
            }
            else if (maze.getCellType(x, y) == CellType::END)
            {
                // Light green color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout << char(206);
                // Reset color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else if (maze.getCellType(x, y) == CellType::PLAYER)
            {
                // Light yellow color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                std::cout << char(207);
                // Reset color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
        }
        std::cout << '\n';
    }
}

// Function overload for drawMaze
void Screen::drawMaze(const Maze &maze, const Player &player, int screenWidth, int screenHeight, char path, char wall, char exit, char playerChar)
{
    const int width = maze.getWidth();
    const int height = maze.getHeight();
    const int startX = maze.getStartX();
    const int startY = maze.getStartY();

    // Resize console window to fit the UI
    const int consoleWidth = screenWidth;
    const int consoleHeight = screenHeight;

    // Draw score and lives
    gotoxy(2, 2);
    // Light blue color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    std::cout << "Score: ";
    // Light yellow color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    std::cout << player.getScore();

    gotoxy(consoleWidth - 12, 2);
    // Light blue color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    std::cout << "Lives: ";
    for (int i = 0; i < player.getLives(); ++i)
    {
        // Light yellow color
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        std::cout << char(playerChar);
        // Reset color
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    // Draw maze and player in the middle of the console
    for (int y = 0; y < height; ++y)
    {
        gotoxy(consoleWidth / 2 - width / 2, 4 + y);
        for (int x = 0; x < width; ++x)
        {
            if (maze.getCellType(x, y) == CellType::WALL)
            {
                // Light black color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                std::cout << char(wall);
                // Reset color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else if ((maze.getCellType(x, y) == CellType::PATH) || (maze.getCellType(x, y) == CellType::START))
            {
                std::cout << char(path);
            }
            else if (maze.getCellType(x, y) == CellType::END)
            {
                // Light green color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                std::cout << char(exit);
                // Reset color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else if (maze.getCellType(x, y) == CellType::PLAYER)
            {
                // Light yellow color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
                std::cout << char(playerChar);
                // Reset color
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
        }
        std::cout << '\n';
    }
}

// Gets needed variables for screen
int Screen::getHeight() const
{
    return height_;
}

int Screen::getWidth() const
{
    return width_;
}

void Screen::setHeight(int height)
{
    height_ = height;
}

void Screen::setWidth(int width)
{
    width_ = width;
}

// Main Screen menu display
void Screen::drawMenu()
{
    gotoxy(1, 1);
    // Red color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    std::cout << R"(   
     _____                           
    |   __|___ ___ ___ ___ ___       
    |   __|_ -|  _| .'| . | -_|      
    |_____|___|___|__,|  _|___|      
    | |_| |_ ___      |_|            
    |  _|   | -_|                    
    |_| |_|_|___|      _     _   _   
    | |___| |_ _ _ ___|_|___| |_| |_ 
    | | .'| . | | |  _| |   |  _|   |
    |_|__,|___|_  |_| |_|_|_|_| |_|_|
              |___|                         
    )" << std::endl;
    // Reset color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    std::cout << "\t1. Play" << std::endl;
    std::cout << "\t2. Exit" << std::endl;
    std::cout << "\t>>: ";
}

// Gameover menu display
void Screen::drawGameOver()
{
    clear();
    gotoxy(1, 1);
    // Red color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    std::cout << R"(
     _____                
    |   __|___ _____ ___  
    |  |  | .'|     | -_| 
    |_____|__,|_|_|_|____ 
    _____             |  |
    |     |_ _ ___ ___|  |
    |  |  | | | -_|  _|__|
    |_____|\_/|___|_| |__|                                                  
    )" << '\n';
    // Reset color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    std::cin.clear();
}
