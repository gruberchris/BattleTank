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
        float movementSpeed = 0.5f;
        float rotationSpeed = 1.f;

        // Methods
        void initTexture();
        void initSprite();

    public:
        PlayerTank();
        virtual ~PlayerTank();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return this->sprite.getPosition(); }

        // Methods
        void update();
        void render(sf::RenderTarget& target);
        void move(const float dirX, const float dirY);
        void rotate(const float degrees);
    };

} // battletank

#endif //BATTLETANK_PLAYERTANK_H
