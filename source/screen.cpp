#include "../headers/screen.hpp"
#include <iostream>

void Screen::clear() {
    std::cout << "\033[2J\033[1;1H";
}
