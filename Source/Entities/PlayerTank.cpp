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
        this->attackCooldown = this->attackCooldownMax;
    }

    PlayerTank::~PlayerTank() {

    }

    void PlayerTank::update() {
        this->updateAttack();
    }

    void PlayerTank::updateAttack() {
        if (this->attackCooldown < this->attackCooldownMax) {
            // This controls the attack rate. The smaller attackRateOfFire is, the slower the attack rate is because
            // it is taking more time to increment attackCooldown to equal attackCooldownMax.
            this->attackCooldown += attackRateOfFire;
        }
    }

    bool PlayerTank::canAttack() {
        if (this->attackCooldown < this->attackCooldownMax) {
            return false;
        }

        // TODO: move this to a proper tank "shoot" method
        this->attackCooldown = 0.f;

        return true;
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