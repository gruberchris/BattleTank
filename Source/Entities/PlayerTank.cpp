//
// Created by Christopher Gruber on 9/17/23.
//

#include <iostream>
#include "PlayerTank.h"

namespace battletank {
    void PlayerTank::initTexture() {
        if (!this->texture.loadFromFile("../Source/Resources/Textures/Tank.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load texture." << std::endl;
        }
    }

    void PlayerTank::initSprite() {
        this->sprite.setTexture(this->texture);
        this->sprite.scale(0.1f, 0.1f);
        this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
        this->sprite.setPosition(200.f, 200.f);
    }

    PlayerTank::PlayerTank() {
        this->initTexture();
        this->initSprite();
    }

    PlayerTank::~PlayerTank() {

    }

    void PlayerTank::update() {

    }

    void PlayerTank::render(sf::RenderTarget &target) {
        target.draw(this->sprite);
    }

    void PlayerTank::move(const float dirX, const float dirY) {
        this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    }

    void PlayerTank::rotate(const float degrees) {
        this->sprite.rotate(this->rotationSpeed * degrees);
    }
} // battletank