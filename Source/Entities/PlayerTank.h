//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_PLAYERTANK_H
#define BATTLETANK_PLAYERTANK_H

#include <SFML/Graphics.hpp>
#include "BaseTank.h"

namespace battletank {

    class PlayerTank {
    private:
        // Members
        sf::Texture hull_texture;
        sf::Sprite hull_sprite;
        sf::Transformable hull_transform;
        sf::Sprite turret_sprite;
        sf::Texture turret_texture;
        sf::Transformable turret_transform;
        float movementSpeed = 0.5f;
        float rotationSpeed = 1.f;
        float attackCooldownMax = 10.f;
        float attackCooldown = 0.f;
        const float attackRateOfFire = 0.035f;

        // Methods
        void setTurretTexture(sf::Texture const* t) { this->turret_texture = *t; }
        sf::Texture getTurretTexture() const { return this->turret_texture; }
        float getMovementSpeed() const { return this->movementSpeed; }
        void setMovementSpeed(float speed) { this->movementSpeed = speed; }
        void initTexture();
        void initSprite();

    protected:
        // Methods
        void updateAttack();

    public:
        PlayerTank();
        PlayerTank(sf::Texture* hull_texture, sf::Texture* turret_texture);
        virtual ~PlayerTank();

        // Accessors
        void setTexture(sf::Texture const* t) { this->hull_texture = *t; }
        sf::Texture getTexture() const { return this->hull_texture; }
        float getRotation() const { return this->hull_transform.getRotation(); }
        sf::Vector2f getPosition() const { return this->hull_transform.getPosition(); }

        // Methods
        void update();
        void draw(sf::RenderTarget &target) const;

        bool canAttack();
        void moveForward();
        void moveBackward();
        void move(float dirX, float dirY);
        void rotate(float degrees);
    };

} // battletank

#endif //BATTLETANK_PLAYERTANK_H
