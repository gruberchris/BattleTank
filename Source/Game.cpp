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
        delete this->window;
        delete this->playerTank;

        // Clean up textures
        for (auto const& [texture_key, texture] : this->textures) {
            delete texture;
        }

        // Clean up tank shell sprites
        for (auto &tank_shell : this->tankShells) {
            delete tank_shell;
        }

        // Clean up enemy tanks sprites
        for (auto &enemy_tank : this->enemyTanks) {
            delete enemy_tank;
        }
    }

    void Game::initWindow() {
        this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Battle Tank", sf::Style::Close | sf::Style::Titlebar);
        this->window->setFramerateLimit(144);
        this->window->setVerticalSyncEnabled(false);
    }

    void Game::initTextures() {
        this->textures["TANK"] = new sf::Texture();
        if (!this->textures["TANK"]->loadFromFile("../Source/Resources/Textures/Tank.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load TANK texture." << std::endl;
        }

        this->textures["TANK_SHELL"] = new sf::Texture();
        if (!this->textures["TANK_SHELL"]->loadFromFile("../Source/Resources/Textures/Light_Shell.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load TANK_SHELL texture." << std::endl;
        }

        this->textures["HULL_A_01"] = new sf::Texture();
        if (!this->textures["HULL_A_01"]->loadFromFile("../Source/Resources/Textures/Hull_A_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load HULL_A_01 texture." << std::endl;
        }

        this->textures["HULL_D_01"] = new sf::Texture();
        if (!this->textures["HULL_D_01"]->loadFromFile("../Source/Resources/Textures/Hull_D_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load HULL_D_01 texture." << std::endl;
        }

        this->textures["GUN_A_01"] = new sf::Texture();
        if (!this->textures["GUN_A_01"]->loadFromFile("../Source/Resources/Textures/Gun_A_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load GUN_A_01 texture." << std::endl;
        }

        this->textures["GUN_D_01"] = new sf::Texture();
        if (!this->textures["GUN_D_01"]->loadFromFile("../Source/Resources/Textures/Gun_D_01.png")) {
            std::cout << "ERROR::GAME::INIT_TEXTURES::Failed to load GUN_D_01 texture." << std::endl;
        }
    }

    void Game::initEnemyTanks() {
        auto hull_texture = this->textures["HULL_D_01"];
        auto gun_texture = this->textures["GUN_D_01"];

        for (int i = 0; i < 10; ++i) {
            auto x = static_cast<float>(rand() % 1920);
            auto y = static_cast<float>(rand() % 1080);
            auto rotation = static_cast<float>(rand() % 360);
            this->enemyTanks.push_back(new EnemyTank(hull_texture, gun_texture, x, y, rotation));
        }

        //this->enemyTanks.push_back(new EnemyTank(hull_texture, gun_texture, 400.f, 400.f, 0.f));
        //this->enemyTanks.push_back(new EnemyTank(hull_texture, gun_texture, 500.f, 400.f, 45.f));
    }

    void Game::initPlayerTank() {
        auto hull_texture = this->textures["HULL_A_01"];
        auto gun_texture = this->textures["GUN_A_01"];

        auto x = static_cast<float>(this->window->getSize().x) / 2.f;
        auto y = static_cast<float>(this->window->getSize().y) / 2.f;
        auto rotation = 0.f;

        this->playerTank = new PlayerTank(hull_texture, gun_texture, x, y, rotation);
    }

    void Game::run() {
        sf::ContextSettings settings = window->getSettings();
        std::cout << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;
        std::cout << "Depth bits: " << settings.depthBits << std::endl;
        std::cout << "Stencil bits: " << settings.stencilBits << std::endl;
        std::cout << "Antialiasing level: " << settings.antialiasingLevel << std::endl;
        std::cout << "OpenGL debug: " << settings.attributeFlags << std::endl;
        std::cout << "SFML version: " << SFML_VERSION_MAJOR << "." << SFML_VERSION_MINOR << "." << SFML_VERSION_PATCH << std::endl;

        while (this->window->isOpen()) {
            this->update();
            this->render();
        }
    }

    void Game::update() {
        this->updatePollEvents();
        this->updateInput();
        this->playerTank->update();
        this->updateTankShells();
        this->updateEnemyTanks();
    }

    void Game::render() {
        this->window->clear();

        this->playerTank->draw(*this->window);

        for (auto *shell : this->tankShells) {
            shell->render(this->window);
        }

        for (auto *enemyTank : this->enemyTanks) {
            enemyTank->render(this->window);
        }

        this->window->display();
    }

    void Game::updatePollEvents() {
        sf::Event event{};

        while (this->window->pollEvent(event)) {
            if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                this->window->close();
            }
        }
    }

    void Game::updateInput() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->playerTank->rotate(-1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->playerTank->rotate(1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->playerTank->moveForward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            this->playerTank->moveBackward();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && this->playerTank->canAttack()) {
            // Get the sprite's rotation in degrees
            float rotation = playerTank->getRotation();

            // Calculate the direction vector based on the sprite's rotation
            float dirX = std::cos((rotation - 90) * toRadians);
            float dirY = std::sin((rotation - 90) * toRadians);

            // Create the tank shell with the calculated direction vector
            this->tankShells.push_back(new TankShell(this->textures["TANK_SHELL"],
                                                     this->playerTank->getPosition().x,
                                                     this->playerTank->getPosition().y,
                                                     dirX,
                                                     dirY,
                                                     rotation,
                                                     6.f));
        }
    }

    void Game::updateTankShells() {
        unsigned counter = 0;

        for (auto *shell : this->tankShells) {
            shell->update();

            if (shell->isOutOfView(this->window)) {
                // Delete tank shell
                delete this->tankShells.at(counter);

                // Cull tank shell from vector as it is out of bounds
                this->tankShells.erase(this->tankShells.begin() + counter);

                --counter;
            }

            // std::cout << this->tankShells.size() << " tank shells remaining." << std::endl;

            ++counter;
        }
    }

    void Game::updateEnemyTanks() {
        unsigned counter = 0;

        for (auto *enemyTank : this->enemyTanks) {
            enemyTank->update();

            if (enemyTank->canAttack()) {
                // Get the sprite's rotation in degrees
                float rotation = enemyTank->getRotation();

                // Calculate the direction vector based on the sprite's rotation
                float dirX = std::cos((rotation - 90) * toRadians);
                float dirY = std::sin((rotation - 90) * toRadians);

                // Create the tank shell with the calculated direction vector
                this->tankShells.push_back(new TankShell(this->textures["TANK_SHELL"],
                                                         enemyTank->getPosition().x,
                                                         enemyTank->getPosition().y,
                                                         dirX,
                                                         dirY,
                                                         rotation,
                                                         6.f));
            }

            ++counter;
        }
    }
} // battletank