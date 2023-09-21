//
// Created by Christopher Gruber on 9/19/23.
//

#ifndef BATTLETANK_TANKSHELL_H
#define BATTLETANK_TANKSHELL_H

#include <SFML/Graphics.hpp>

namespace battletank {

    class TankShell {
    private:
        sf::Sprite sprite;
        sf::Vector2f direction;
        float movementSpeed;

    public:
        TankShell();
        TankShell(const sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed);
        virtual ~TankShell();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }

        // Methods
        void update();
        void render(sf::RenderTarget* target);
        bool isOutOfViewTop();
        bool isOutOfViewBottom(sf::RenderTarget* target);
        bool isOutOfViewLeft();
        bool isOutOfViewRight(sf::RenderTarget* target);
        bool isOutOfView(sf::RenderTarget* target);
    };

} // battletank

#endif //BATTLETANK_TANKSHELL_H
