//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_PLAYERTANK_H
#define BATTLETANK_PLAYERTANK_H

#include <SFML/Graphics.hpp>

namespace battletank {

    class PlayerTank {
    private:
        // Members
        sf::Texture mHullTexture;
        sf::Sprite mHullSprite;
        sf::Sprite mTurretSprite;
        sf::Texture mTurretTexture;
        float mMovementSpeed = 0.5f;
        float mRotationSpeed = 1.f;
        float mAttackCooldownMax = 6.5f;
        float mAttackCooldown = 0.f;
        const float mAttackRateOfFire = 0.035f;

        sf::Rect<float> mHullBounds;

        // Methods
        void initSprite(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation);

    protected:
        // Methods
        void updateAttack();

    public:
        PlayerTank(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation);
        virtual ~PlayerTank();

        // Accessors
        void setHullTexture(const sf::Texture* texture) { this->mHullTexture = *texture; }
        sf::Texture getHullTexture() const { return this->mHullTexture; }
        void setTurretTexture(sf::Texture const* texture) { this->mTurretTexture = *texture; }
        sf::Texture getTurretTexture() const { return this->mTurretTexture; }
        float getMovementSpeed() const { return this->mMovementSpeed; }
        void setMovementSpeed(float movementSpeed) { this->mMovementSpeed = movementSpeed; }

        void setHullBounds(sf::Rect<float> hullBounds) { this->mHullBounds = hullBounds; }
        sf::FloatRect getHullBounds() const { return this->mHullSprite.getTransform().transformRect(mHullBounds); }

        float getRotation() const { return this->mHullSprite.getRotation(); }
        sf::Vector2f getPosition() const { return this->mHullSprite.getPosition(); }
        sf::FloatRect getGlobalBounds() const { return this->mHullSprite.getGlobalBounds(); }

        // Methods
        void update();
        void draw(sf::RenderTarget &target) const;

        bool canAttack();
        void moveForward();
        void moveBackward();
        void move(float dirX, float dirY);
        void rotate(float degrees);
        sf::Vector2f getMuzzlePosition() const;
        bool checkOBBIntersection(sf::FloatRect otherBounds) const;
    };

} // battletank

#endif //BATTLETANK_PLAYERTANK_H
