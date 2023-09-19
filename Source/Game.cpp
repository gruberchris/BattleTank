//
// Created by Christopher Gruber on 9/17/23.
//

#include "Game.h"

namespace battletank {
    void Game::initWindow() {
        this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Battle Tank", sf::Style::Close | sf::Style::Titlebar);
        this->window->setFramerateLimit(144);
        this->window->setVerticalSyncEnabled(false);
    }

    void Game::initPlayerTank() {
        this->playerTank = new PlayerTank();
    }

    Game::Game() {
        this->initWindow();
        this->initPlayerTank();
    }

    Game::~Game() {
        delete this->window;
        delete this->playerTank;
    }

    void Game::run() {
        while (this->window->isOpen()) {
            this->update();
            this->render();
        }
    }

    void Game::update() {
        sf::Event event{};

        while (this->window->pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    this->window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        this->window->close();
                    }

                    if (event.key.code == sf::Keyboard::A) {
                        this->playerTank->rotate(-1.f);
                    }

                    if (event.key.code == sf::Keyboard::D) {
                        this->playerTank->rotate(1.f);
                    }

                    if (event.key.code == sf::Keyboard::W) {
                        this->playerTank->move(0.f, -1.f);
                    }

                    if (event.key.code == sf::Keyboard::S) {
                        this->playerTank->move(0.f, 1.f);
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void Game::render() {
        this->window->clear();

        this->playerTank->render(*this->window);

        this->window->display();
    }
} // battletank