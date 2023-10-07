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

    bool EnemyTank::checkOBBIntersection(sf::FloatRect otherBounds) const {
        // Check for Oriented Bounding Box (OBB) intersection
        // https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
        // https://stackoverflow.com/questions/10962379/how-to-check-intersection-between-2-rotated-rectangles
        // https://stackoverflow.com/questions/18792207/rotate-a-bounding-box

        // Get the center of the otherBounds
        const float otherBoundsCenterX = otherBounds.left + otherBounds.width / 2.f;
        const float otherBoundsCenterY = otherBounds.top + otherBounds.height / 2.f;

        // Get the center of the hullBounds
        const float hullBoundsCenterX = this->mHullSprite.getPosition().x;
        const float hullBoundsCenterY = this->mHullSprite.getPosition().y;

        // Get the angle between the two rectangles
        const float angle = this->mHullSprite.getRotation() * (float)M_PI / 180.f;

        // Get the distance between the two rectangles
        const float distanceX = otherBoundsCenterX - hullBoundsCenterX;
        const float distanceY = otherBoundsCenterY - hullBoundsCenterY;

        // Rotate the distance around the origin
        const float rotatedDistanceX = std::cos(angle) * distanceX + std::sin(angle) * distanceY;
        const float rotatedDistanceY = -std::sin(angle) * distanceX + std::cos(angle) * distanceY;

        const float kBoundingBoxScale = 6.f;

        // Check if the rotated distance is less than the sum of the half widths and half heights
        if (std::abs(rotatedDistanceX) < this->mHullSprite.getGlobalBounds().width / kBoundingBoxScale + otherBounds.width / kBoundingBoxScale &&
            std::abs(rotatedDistanceY) < this->mHullSprite.getGlobalBounds().height / kBoundingBoxScale + otherBounds.height / kBoundingBoxScale) {
            return true;
        }

        return false;
    }

    sf::Vector2f EnemyTank::getMuzzlePosition() const {
        const float kMuzzleOffset = 20.f;
        const float dirX = std::cos((this->mTurretSprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = std::sin((this->mTurretSprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float muzzlePosX = this->mTurretSprite.getPosition().x + dirX * kMuzzleOffset;
        const float muzzlePosY = this->mTurretSprite.getPosition().y + dirY * kMuzzleOffset;
        return {muzzlePosX, muzzlePosY};
    }
} // battletank