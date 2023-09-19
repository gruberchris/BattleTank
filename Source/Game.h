//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_GAME_H
#define BATTLETANK_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Entities/PlayerTank.h"

namespace battletank {
    class Game {
    private:
        sf::RenderWindow* window;
        PlayerTank* playerTank;

        // Methods
        void initWindow();
        void initPlayerTank();

    public:
        Game();
        virtual ~Game();

        // Accessors

        // Methods
        void run();
        void update();
        void render();
    };

} // battletank

#endif //BATTLETANK_GAME_H
