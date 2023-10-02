#include "Game.h"

using namespace battletank;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Game game;

    game.run();

    return 0;
}
