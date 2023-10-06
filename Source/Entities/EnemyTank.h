//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_ENEMYTANK_H
#define BATTLETANK_ENEMYTANK_H

#include <SFML/Graphics.hpp>

namespace battletank {

    class EnemyTank {
    private:
        sf::Sprite mHullSprite;
        sf::Texture mHullTexture;
        sf::Sprite mTurretSprite;
        sf::Texture mTurretTexture;
        float mMovementSpeed = 0.5f;
        float mRotationSpeed = 1.f;
        float mAttackCooldownMax = 10.f;
        float mAttackCooldown = 0.f;
        const float mAttackRateOfFire = 0.035f;

        // Methods
        void initSprite(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation);
        void setTexture(sf::Texture const* texture) { this->mHullTexture = *texture; }
        sf::Texture getTexture() const { return this->mHullTexture; }
        void setTurretTexture(sf::Texture const* texture) { this->mTurretTexture = *texture; }
        sf::Texture getTurretTexture() const { return this->mTurretTexture; }

    public:
        EnemyTank(const sf::Texture* hullTexture, const sf::Texture* turretTexture, float posX, float posY, float rotation);
        virtual ~EnemyTank();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->mHullSprite.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return this->mHullSprite.getPosition(); }
        float getRotation() const { return this->mHullSprite.getRotation(); }
        sf::Vector2f getOrigin() const { return this->mHullSprite.getOrigin(); }

        // Methods
        void update();
        void render(sf::RenderTarget* target);

        void move(const float dirX, const float dirY);
        void rotate(const float degrees);
        void updateAttack();
        bool canAttack();


    };

} // battletank

#endif //BATTLETANK_ENEMYTANK_H
