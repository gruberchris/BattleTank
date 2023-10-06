//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_GAME_H
#define BATTLETANK_GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "Entities/PlayerTank.h"
#include "Entities/TankShell.h"
#include "Entities/EnemyTank.h"

namespace battletank {
    class Game {
    private:
        sf::RenderWindow* mWindow;
        PlayerTank* mPlayerTank;
        std::map<std::string, sf::Texture*> mTextures;
        std::vector<TankShell*> mTankShells;
        std::vector<EnemyTank*> mEnemyTanks;
        const float kToRadians = static_cast<float>(M_PI / 180.f);

        // Methods
        void initWindow();
        void initTextures();
        void initPlayerTank();
        void initEnemyTanks();

    public:
        Game();
        virtual ~Game();

        // Accessors

        // Methods
        void run();
        void update();
        void render();
        void updatePollEvents();
        void updateInput();
        void updateTankShells();
        void updateEnemyTanks();
    };

} // battletank

#endif //BATTLETANK_GAME_H
