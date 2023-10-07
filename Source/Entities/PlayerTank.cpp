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

        // Initialize hull bounds
        this->mHullBounds = {1.f, 1.f, 200.f, 250.f};

        //this->mHullBounds = sf::Rect<float>(this->mHullSprite.getLocalBounds().left, this->mHullSprite.getLocalBounds().top, this->mHullSprite.getLocalBounds().width, this->mHullSprite.getLocalBounds().height);
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

    sf::Vector2f PlayerTank::getMuzzlePosition() const {
        const float kMuzzleOffset = 20.f;
        const float dirX = std::cos((this->mTurretSprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float dirY = std::sin((this->mTurretSprite.getRotation() - 90) * (float)M_PI / 180.f);
        const float muzzlePosX = this->mTurretSprite.getPosition().x + dirX * kMuzzleOffset;
        const float muzzlePosY = this->mTurretSprite.getPosition().y + dirY * kMuzzleOffset;
        return {muzzlePosX, muzzlePosY};
    }

    bool PlayerTank::checkOBBIntersection(sf::FloatRect otherBounds) const {
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
} // battletank