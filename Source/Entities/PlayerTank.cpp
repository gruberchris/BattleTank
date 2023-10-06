//
// Created by Christopher Gruber on 9/17/23.
//

#include "PlayerTank.h"

namespace battletank {
    PlayerTank::PlayerTank(sf::Texture* texture, sf::Texture* turret_texture, float posX, float posY, float rotation) {
        this->initSprite(texture, turret_texture, posX, posY, rotation);
        this->attackCooldown = this->attackCooldownMax;
    }

    PlayerTank::~PlayerTank() {

    }

    void PlayerTank::initSprite(const sf::Texture* hull_texture, const sf::Texture* turret_texture, float posX, float posY, float rotation) {
        // Initialize tank hull
        this->hull_sprite.setTexture(*hull_texture);
        this->hull_sprite.scale(0.25f, 0.25f);
        this->hull_sprite.setOrigin(this->hull_sprite.getLocalBounds().width / 2.f, this->hull_sprite.getLocalBounds().height / 2.f);
        this->hull_sprite.setPosition(posX, posY);
        this->hull_sprite.setRotation(rotation);

        // Initialize tank turret
        this->turret_sprite.setTexture(*turret_texture);
        this->turret_sprite.scale(0.25f, 0.25f);
        this->turret_sprite.setOrigin(this->turret_sprite.getLocalBounds().width / 2.f, this->turret_sprite.getLocalBounds().height / 2.f);
        this->turret_sprite.setPosition(this->hull_sprite.getPosition());
        this->turret_sprite.setRotation(rotation);
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
        //target.draw(this->hull_sprite, this->hull_sprite.getTransform());
        //target.draw(this->turret_sprite, this->turret_sprite.getTransform());
        target.draw(this->hull_sprite);
        target.draw(this->turret_sprite);
    }

    void PlayerTank::rotate(const float degrees) {
        auto rotationChange = this->rotationSpeed * degrees;
        this->hull_sprite.rotate(rotationChange);
        this->turret_sprite.rotate(rotationChange);
    }

    void PlayerTank::move(const float dirX, const float dirY) {
        auto movementVector = sf::Vector2f(this->movementSpeed * dirX, this->movementSpeed * dirY);
        this->hull_sprite.move(movementVector);
        this->turret_sprite.move(movementVector);
    }

    void PlayerTank::moveForward() {
        const float dirX = std::cos((this->hull_sprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = std::sin((this->hull_sprite.getRotation() - 90) * (float)M_PI / 180.f);
        this->move(dirX, dirY);
    }

    void PlayerTank::moveBackward() {
        const float dirX = -std::cos((this->hull_sprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = -std::sin((this->hull_sprite.getRotation() - 90) * (float)M_PI / 180.f);
        this->move(dirX, dirY);
    }
} // battletank