#include "Game.h"

using namespace battletank;

int main() {
    srand(std::time_t(static_cast<unsigned>(0)));

    Game game;

    game.run();

    return 0;
}
