//
// Created by Christopher Gruber on 9/17/23.
//

#include "EnemyTank.h"

namespace battletank {
    EnemyTank::EnemyTank(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation) {
        initSprite(hullTexture, turretTexture, posX, posY, rotation);
        this->mAttackCooldown = this->mAttackCooldownMax;
    }

    EnemyTank::~EnemyTank() = default;

    void EnemyTank::initSprite(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation) {
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

    void EnemyTank::update() {
        this->updateAttack();
    }

    void EnemyTank::updateAttack() {
        if (this->mAttackCooldown < this->mAttackCooldownMax) {
            // This controls the attack rate. The smaller attackRateOfFire is, the slower the attack rate is because
            // it is taking more time to increment attackCooldown to equal attackCooldownMax.
            this->mAttackCooldown += mAttackRateOfFire;
        }
    }

    bool EnemyTank::canAttack() {
        if (this->mAttackCooldown < this->mAttackCooldownMax) {
            return false;
        }

        // TODO: move this to a proper tank "shoot" method
        this->mAttackCooldown = 0.f;

        return true;
    }

    void EnemyTank::draw(sf::RenderTarget *target) const {
        target->draw(this->mHullSprite);
        target->draw(this->mTurretSprite);
    }

    void EnemyTank::move(const float dirX, const float dirY) {
        this->mHullSprite.move(this->mMovementSpeed * dirX, this->mMovementSpeed * dirY);
        this->mTurretSprite.move(this->mMovementSpeed * dirX, this->mMovementSpeed * dirY);
    }

    void EnemyTank::rotate(const float degrees) {
        this->mHullSprite.rotate(this->mRotationSpeed * degrees);
        this->mTurretSprite.rotate(this->mRotationSpeed * degrees);
    }
} // battletank