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

    void PlayerTank::initSprite(sf::Texture* hull_texture, sf::Texture* turret_texture, float posX, float posY, float rotation) {
        // Initialize tank hull
        this->hull_sprite.setTexture(*hull_texture);
        this->hull_transform.scale(0.25f, 0.25f);
        this->hull_transform.setOrigin(this->hull_sprite.getLocalBounds().width / 2.f, this->hull_sprite.getLocalBounds().height / 2.f);
        this->hull_transform.setPosition(posX, posY);
        this->hull_transform.setRotation(rotation);

        // Initialize tank turret
        this->turret_sprite.setTexture(*turret_texture);
        this->turret_transform.scale(0.25f, 0.25f);
        this->turret_transform.setOrigin(this->turret_sprite.getLocalBounds().width / 2.f, this->turret_sprite.getLocalBounds().height / 2.f);
        this->turret_transform.setPosition(this->hull_transform.getPosition());
        this->turret_transform.setRotation(rotation);
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