//
// Created by Christopher Gruber on 9/17/23.
//

#include <iostream>
#include "PlayerTank.h"

namespace battletank {
    PlayerTank::PlayerTank() {
        // TODO: the default constructor should not be used
        this->initTexture();
        this->initSprite();
        this->attackCooldown = this->attackCooldownMax;
    }

    PlayerTank::PlayerTank(sf::Texture* texture, sf::Texture* turret_texture) {
        setTexture(texture);
        setTurretTexture(turret_texture);
        this->initSprite();
        this->attackCooldown = this->attackCooldownMax;
    }

    PlayerTank::~PlayerTank() {

    }

    void PlayerTank::initTexture() {
        if (!this->hull_texture.loadFromFile("../Source/Resources/Textures/Hull_A_01.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load hull texture." << std::endl;
        }

        if (!this->turret_texture.loadFromFile("../Source/Resources/Textures/Gun_A_01.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load turret texture." << std::endl;
        }
    }

    void PlayerTank::initSprite() {
        // Initialize tank hull
        this->hull_sprite.setTexture(this->hull_texture);
        this->hull_transform.scale(0.25f, 0.25f);
        this->hull_transform.setOrigin(this->hull_sprite.getLocalBounds().width / 2.f, this->hull_sprite.getLocalBounds().height / 2.f);
        this->hull_transform.setPosition(200.f, 200.f);

        // Initialize tank turret
        this->turret_sprite.setTexture(this->turret_texture);
        this->turret_transform.scale(0.25f, 0.25f);
        this->turret_transform.setOrigin(this->turret_sprite.getLocalBounds().width / 2.f, this->turret_sprite.getLocalBounds().height / 2.f);
        this->turret_transform.setPosition(this->hull_transform.getPosition());
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

    void PlayerTank::draw(sf::RenderTarget &target) const {
        target.draw(this->hull_sprite, this->hull_transform.getTransform());
        target.draw(this->turret_sprite, this->turret_transform.getTransform());
    }

    void PlayerTank::rotate(const float degrees) {
        this->hull_transform.rotate(this->rotationSpeed * degrees);
        this->turret_transform.rotate(this->rotationSpeed * degrees);
    }

    void PlayerTank::move(const float dirX, const float dirY) {
        this->hull_transform.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
        this->turret_transform.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    }

    void PlayerTank::moveForward() {
        const float dirX = std::cos((this->hull_transform.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = std::sin((this->hull_transform.getRotation() - 90) * (float)M_PI / 180.f);
        this->move(dirX, dirY);
    }

    void PlayerTank::moveBackward() {
        const float dirX = -std::cos((this->hull_transform.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = -std::sin((this->hull_transform.getRotation() - 90) * (float)M_PI / 180.f);
        this->move(dirX, dirY);
    }
} // battletank