//
// Created by Christopher Gruber on 9/17/23.
//

#include <iostream>
#include "PlayerTank.h"

namespace battletank {
    void PlayerTank::initTexture() {
        if (!this->texture.loadFromFile("../Source/Resources/Textures/Hull_A_01.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load hull texture." << std::endl;
        }

        if (!this->turret_texture.loadFromFile("../Source/Resources/Textures/Gun_A_01.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load turret texture." << std::endl;
        }
    }

    void PlayerTank::initSprite() {
        this->sprite.setTexture(this->texture);
        this->sprite.scale(0.25f, 0.25f);
        this->sprite.setOrigin(this->sprite.getLocalBounds().width / 2.f, this->sprite.getLocalBounds().height / 2.f);
        this->sprite.setPosition(200.f, 200.f);

        this->turret_sprite.setTexture(this->turret_texture);
        this->turret_sprite.scale(0.25f, 0.25f);
        this->turret_sprite.setOrigin(this->turret_sprite.getLocalBounds().width / 2.f, this->turret_sprite.getLocalBounds().height / 2.f);
        this->turret_sprite.setPosition(this->sprite.getPosition());
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
        target.draw(this->turret_sprite);
    }

    void PlayerTank::move(const float dirX, const float dirY) {
        this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
        this->turret_sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    }

    void PlayerTank::moveForward() {
        this->move(std::cos((this->sprite.getRotation() - 90) * M_PI / 180.f), std::sin((this->sprite.getRotation() - 90) * M_PI / 180.f));
    }

    void PlayerTank::moveBackward() {
        this->move(-std::cos((this->sprite.getRotation() - 90) * M_PI / 180.f), -std::sin((this->sprite.getRotation() - 90) * M_PI / 180.f));
    }

    void PlayerTank::rotate(const float degrees) {
        this->sprite.rotate(this->rotationSpeed * degrees);
        this->turret_sprite.rotate(this->rotationSpeed * degrees);
    }
} // battletank