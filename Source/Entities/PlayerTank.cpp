//
// Created by Christopher Gruber on 9/17/23.
//

#include "PlayerTank.h"

namespace battletank {
    PlayerTank::PlayerTank(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation) {
        this->initSprite(hullTexture, turretTexture, posX, posY, rotation);
        this->mAttackCooldown = this->mAttackCooldownMax;
    }

    PlayerTank::~PlayerTank() = default;

    void PlayerTank::initSprite(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation) {
        // Initialize tank hull
        this->mHullSprite.setTexture(*hullTexture);
        this->mHullSprite.scale(0.25f, 0.25f);
        this->mHullSprite.setOrigin(this->mHullSprite.getLocalBounds().width / 2.f, this->mHullSprite.getLocalBounds().height / 2.f);
        this->mHullSprite.setPosition(posX, posY);
        this->mHullSprite.setRotation(rotation);

        // Initialize tank turret
        this->mTurretSprite.setTexture(*turretTexture);
        this->mTurretSprite.scale(0.25f, 0.25f);
        this->mTurretSprite.setOrigin(this->mTurretSprite.getLocalBounds().width / 2.f, this->mTurretSprite.getLocalBounds().height / 2.f);
        this->mTurretSprite.setPosition(this->mHullSprite.getPosition());
        this->mTurretSprite.setRotation(rotation);
    }

    void PlayerTank::update() {
        this->updateAttack();
    }

    void PlayerTank::updateAttack() {
        if (this->mAttackCooldown < this->mAttackCooldownMax) {
            // This controls the attack rate. The smaller attackRateOfFire is, the slower the attack rate is because
            // it is taking more time to increment attackCooldown to equal attackCooldownMax.
            this->mAttackCooldown += mAttackRateOfFire;
        }
    }

    bool PlayerTank::canAttack() {
        if (this->mAttackCooldown < this->mAttackCooldownMax) {
            return false;
        }

        // TODO: move this to a proper tank "shoot" method
        this->mAttackCooldown = 0.f;

        return true;
    }

    void PlayerTank::draw(sf::RenderTarget &target) const {
        target.draw(this->mHullSprite);
        target.draw(this->mTurretSprite);
    }

    void PlayerTank::rotate(const float degrees) {
        auto rotationChange = this->mRotationSpeed * degrees;
        this->mHullSprite.rotate(rotationChange);
        this->mTurretSprite.rotate(rotationChange);
    }

    void PlayerTank::move(const float dirX, const float dirY) {
        auto movementVector = sf::Vector2f(this->mMovementSpeed * dirX, this->mMovementSpeed * dirY);
        this->mHullSprite.move(movementVector);
        this->mTurretSprite.move(movementVector);
    }

    void PlayerTank::moveForward() {
        const float dirX = std::cos((this->mHullSprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = std::sin((this->mHullSprite.getRotation() - 90) * (float)M_PI / 180.f);
        this->move(dirX, dirY);
    }

    void PlayerTank::moveBackward() {
        const float dirX = -std::cos((this->mHullSprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = -std::sin((this->mHullSprite.getRotation() - 90) * (float)M_PI / 180.f);
        this->move(dirX, dirY);
    }
} // battletank