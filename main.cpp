#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include <ctime>   // time()
#include "Game.h"
#include "Board.h"
using namespace std;
using namespace sf;

int main(){
    
    srand(time(NULL));
    Game game; // my game
    game.runMainWindow();

    return 0;
}