// main.cpp
#include "headers/game.hpp"

int main() {
    //Set lybrinth size
    Game game(11, 11);
    //Start game command
    game.init();

    system("pause");
    return 0;
}
