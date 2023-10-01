//
// Created by Christopher Gruber on 9/17/23.
//

#include <iostream>
#include "EnemyTank.h"

namespace battletank {
    EnemyTank::EnemyTank(sf::Texture* hull_texture, sf::Texture* turret_texture, float posX, float posY, float rotation) {
        initSprite(hull_texture, turret_texture, posX, posY, rotation);
    }

    EnemyTank::~EnemyTank() {

    }

    /*
    void EnemyTank::initTexture() {
        if (!this->hull_texture.loadFromFile("../Source/Resources/Textures/Hull_D_01.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load hull texture." << std::endl;
        }

        if (!this->turret_texture.loadFromFile("../Source/Resources/Textures/Gun_D_01.png")) {
            std::cout << "ERROR::PLAYER_TANK::INIT_TEXTURE::Failed to load tank texture." << std::endl;
        }
    }
    */

    void EnemyTank::initSprite(sf::Texture* hull_texture, sf::Texture* turret_texture, float posX, float posY, float rotation) {
        this->hull_sprite.setTexture(*hull_texture);
        this->hull_sprite.scale(0.25f, 0.25f);
        this->hull_sprite.setOrigin(this->hull_sprite.getLocalBounds().width / 2.f, this->hull_sprite.getLocalBounds().height / 2.f);
        this->hull_sprite.setPosition(posX, posY);
        this->hull_sprite.setRotation(rotation);

        this->turret_sprite.setTexture(*turret_texture);
        this->turret_sprite.scale(0.25f, 0.25f);
        this->turret_sprite.setOrigin(this->turret_sprite.getLocalBounds().width / 2.f, this->turret_sprite.getLocalBounds().height / 2.f);
        this->turret_sprite.setPosition(this->hull_sprite.getPosition());
        this->turret_sprite.setRotation(rotation);
    }

    void EnemyTank::update() {
        this->updateAttack();
    }

    void EnemyTank::updateAttack() {
        if (this->attackCooldown < this->attackCooldownMax) {
            // This controls the attack rate. The smaller attackRateOfFire is, the slower the attack rate is because
            // it is taking more time to increment attackCooldown to equal attackCooldownMax.
            this->attackCooldown += attackRateOfFire;
        }
    }

    bool EnemyTank::canAttack() {
        if (this->attackCooldown < this->attackCooldownMax) {
            return false;
        }

        // TODO: move this to a proper tank "shoot" method
        this->attackCooldown = 0.f;

        return true;
    }

    void EnemyTank::render(sf::RenderTarget *target) {
        target->draw(this->hull_sprite);
        target->draw(this->turret_sprite);
    }

    void EnemyTank::move(const float dirX, const float dirY) {
        this->hull_sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
        this->turret_sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
    }

    void EnemyTank::rotate(const float degrees) {
        this->hull_sprite.rotate(this->rotationSpeed * degrees);
        this->turret_sprite.rotate(this->rotationSpeed * degrees);
    }
} // battletank