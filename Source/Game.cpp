//
// Created by Christopher Gruber on 9/17/23.
//

#include <iostream>
#include "Game.h"

namespace battletank {
    Game::Game() {
        this->initWindow();
        this->initTextures();
        this->initEnemyTanks();
        this->initPlayerTank();
    }

    Game::~Game() {
        delete this->mWindow;
        delete this->mPlayerTank;

        // Clean up textures
        for (auto const& [textureKey, texture] : this->mTextures) {
            delete texture;
        }

        // Clean up tank shell sprites
        for (auto &tankShell : this->mTankShells) {
            delete tankShell;
        }

        // Clean up enemy tanks sprites
        for (auto &enemyTank : this->mEnemyTanks) {
            delete enemyTank;
        }
    }

    void Game::initWindow() {
        this->mWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Battle Tank", sf::Style::Close | sf::Style::Titlebar);
        this->mWindow->setFramerateLimit(144);
        this->mWindow->setVerticalSyncEnabled(false);
    }

    void Game::initTextures() {
        this->mTextures["TANK"] = new sf::Texture();
        if (!this->mTextures["TANK"]->loadFromFile("../Source/Resources/Textures/Tank.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load TANK texture." << std::endl;
        }

        this->mTextures["TANK_SHELL"] = new sf::Texture();
        if (!this->mTextures["TANK_SHELL"]->loadFromFile("../Source/Resources/Textures/Light_Shell.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load TANK_SHELL texture." << std::endl;
        }

        this->mTextures["HULL_A_01"] = new sf::Texture();
        if (!this->mTextures["HULL_A_01"]->loadFromFile("../Source/Resources/Textures/Hull_A_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load HULL_A_01 texture." << std::endl;
        }

        this->mTextures["HULL_D_01"] = new sf::Texture();
        if (!this->mTextures["HULL_D_01"]->loadFromFile("../Source/Resources/Textures/Hull_D_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load HULL_D_01 texture." << std::endl;
        }

        this->mTextures["GUN_A_01"] = new sf::Texture();
        if (!this->mTextures["GUN_A_01"]->loadFromFile("../Source/Resources/Textures/Gun_A_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load GUN_A_01 texture." << std::endl;
        }

        this->mTextures["GUN_D_01"] = new sf::Texture();
        if (!this->mTextures["GUN_D_01"]->loadFromFile("../Source/Resources/Textures/Gun_D_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load GUN_D_01 texture." << std::endl;
        }
    }

    void Game::initEnemyTanks() {
        auto hullTexture = this->mTextures["HULL_D_01"];
        auto gunTexture = this->mTextures["GUN_D_01"];

        for (int i = 0; i < 5; ++i) {
            // TODO: randomize spawn location
            auto x = static_cast<float>(rand() % 1920);
            auto y = static_cast<float>(rand() % 1080);

            // TODO: randomize rotation
            auto rotation = static_cast<float>(rand() % 360);

            this->mEnemyTanks.push_back(new EnemyTank(hullTexture, gunTexture, x, y, rotation));
        }
    }

    void Game::initPlayerTank() {
        auto hullTexture = this->mTextures["HULL_A_01"];
        auto gunTexture = this->mTextures["GUN_A_01"];

        auto x = static_cast<float>(this->mWindow->getSize().x) / 2.f;
        auto y = static_cast<float>(this->mWindow->getSize().y) / 2.f;
        auto rotation = 0.f;

        this->mPlayerTank = new PlayerTank(hullTexture, gunTexture, x, y, rotation);
    }

    void Game::run() {
        sf::ContextSettings settings = mWindow->getSettings();
        std::cout << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;
        std::cout << "Depth bits: " << settings.depthBits << std::endl;
        std::cout << "Stencil bits: " << settings.stencilBits << std::endl;
        std::cout << "Antialiasing level: " << settings.antialiasingLevel << std::endl;
        std::cout << "OpenGL debug: " << settings.attributeFlags << std::endl;
        std::cout << "SFML version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;

        while (this->mWindow->isOpen()) {
            this->update();
            this->render();
        }
    }

    void Game::update() {
        this->updatePollEvents();
        this->updateInput();
        this->updateTankShells();
        this->mPlayerTank->update();
        this->updateEnemyTanks();
    }

    void Game::render() {
        this->mWindow->clear();

        this->mPlayerTank->draw(*this->mWindow);

        for (auto *shell : this->mTankShells) {
            shell->render(this->mWindow);
        }

        for (auto *enemyTank : this->mEnemyTanks) {
            enemyTank->render(this->mWindow);
        }

        this->mWindow->display();
    }

    void Game::updatePollEvents() {
        sf::Event event{};

        while (this->mWindow->pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                this->mWindow->close();
            }
        }
    }

    void Game::updateInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->mPlayerTank->rotate(-1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->mPlayerTank->rotate(1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->mPlayerTank->moveForward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            this->mPlayerTank->moveBackward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->mPlayerTank->canAttack()) {
            // Get the sprite's rotation in degrees
            float rotation = mPlayerTank->getRotation();

            // Calculate the direction vector based on the sprite's rotation
            float dirX = std::cos((rotation - 90) * kToRadians);
            float dirY = std::sin((rotation - 90) * kToRadians);

            //auto playerTankPos = this->playerTank->getPosition();
            //float distanceInFrontOfTank = 80.f;
            //auto shellPosX = playerTankPos.x + (dirX * distanceInFrontOfTank);
            //auto shellPosY = playerTankPos.y + (dirY * distanceInFrontOfTank);

            // Create the tank shell with the calculated direction vector
            this->mTankShells.push_back(new TankShell(this->mTextures["TANK_SHELL"],
                                                      this->mPlayerTank->getPosition().x,
                                                      this->mPlayerTank->getPosition().y,
                                                      dirX,
                                                      dirY,
                                                      rotation,
                                                      12.f));
        }
    }

    void Game::updateTankShells() {
        for (auto *shell : this->mTankShells) {
            shell->update();

            if (shell->isOutOfView(this->mWindow)) {
                auto tankShellItr = std::ranges::find(this->mTankShells.begin(), this->mTankShells.end(), shell);
                auto tankShellIndex = tankShellItr - this->mTankShells.begin();

                // Delete tank shell
                delete this->mTankShells.at(tankShellIndex);

                // Cull tank shell from vector as it is out of bounds
                this->mTankShells.erase(this->mTankShells.begin() + tankShellIndex);

                continue;
            }

            // TODO: Fix sprite collision detection. Projectiles are colliding with the tank that fired them
            continue;

            // Check tank shell hit with player tank
            if (this->mPlayerTank->getBoundingBox().intersects(shell->getGlobalBounds())) {
                auto tankShellItr = std::ranges::find(this->mTankShells.begin(), this->mTankShells.end(), shell);
                auto tankShellIndex = tankShellItr - this->mTankShells.begin();

                // Delete tank shell
                delete this->mTankShells.at(tankShellIndex);

                // Cull tank shell from vector as it is out of bounds
                this->mTankShells.erase(this->mTankShells.begin() + tankShellIndex);

                // TODO: do damage or kill player tank

                std::cout << "Player tank hit!" << std::endl;
            }

            /*
            else {
                // Check tank shell hit with enemy tanks
                for (auto *enemyTank: this->enemyTanks) {
                    if (shell->getGlobalBounds().intersects(enemyTank->getBoundingBox())) {
                        // Check if tank shell was already deleted
                        if (this->tankShells.size() <= counter || this->tankShells.at(counter) == nullptr) {
                            break;
                        }

                        // Delete tank shell
                        delete this->tankShells.at(counter);

                        // Cull tank shell from vector
                        this->tankShells.erase(this->tankShells.begin() + counter);

                        // TODO: do damage or kill enemy tank

                        std::cout << "Enemy tank hit!" << std::endl;

                        --counter;
                    }
                }
            }

             */

            //std::cout << this->tankShells.size() << " tank shells remaining." << std::endl;
        }
    }

    void Game::updateEnemyTanks() {
        unsigned counter = 0;

        for (auto *enemyTank : this->mEnemyTanks) {
            enemyTank->update();

            if (enemyTank->canAttack()) {
                // Get the sprite's rotation in degrees
                float rotation = enemyTank->getRotation();

                // Calculate the direction vector based on the sprite's rotation
                float dirX = std::cos((rotation - 90) * kToRadians);
                float dirY = std::sin((rotation - 90) * kToRadians);

                // Create the tank shell with the calculated direction vector
                this->mTankShells.push_back(new TankShell(this->mTextures["TANK_SHELL"],
                                                          enemyTank->getPosition().x,
                                                          enemyTank->getPosition().y,
                                                          dirX,
                                                          dirY,
                                                          rotation,
                                                          12.f));
            }

            ++counter;
        }
    }
} // battletank