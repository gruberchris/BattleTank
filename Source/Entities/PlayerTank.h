//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_PLAYERTANK_H
#define BATTLETANK_PLAYERTANK_H

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace battletank {

    class PlayerTank {
    private:
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Sprite turret_sprite;
        sf::Texture turret_texture;
        float movementSpeed = 0.5f;
        float rotationSpeed = 1.f;
        float attackCooldownMax = 10.f;
        float attackCooldown = 0.f;
        const float attackRateOfFire = 0.035f;

        // Methods
        void initTexture();
        void initSprite();

    public:
        PlayerTank();
        virtual ~PlayerTank();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return this->sprite.getPosition(); }
        float getRotation() const { return this->sprite.getRotation(); }

        // Methods
        void update();
        void updateAttack();
        bool canAttack();
        void render(sf::RenderTarget& target);
        void moveForward();
        void moveBackward();
        void move(const float dirX, const float dirY);
        void rotate(const float degrees);
    };

} // battletank

#endif //BATTLETANK_PLAYERTANK_H
