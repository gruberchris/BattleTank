//
// Created by Christopher Gruber on 9/19/23.
//

#ifndef BATTLETANK_TANKSHELL_H
#define BATTLETANK_TANKSHELL_H

#include <SFML/Graphics.hpp>

namespace battletank {

    class TankShell {
    private:
        sf::Sprite m_sprite;
        sf::Vector2f m_direction;
        float m_movementSpeed = 12.f;

    public:
        TankShell(const sf::Texture* texture, float posX, float posY, float dirX, float dirY, float rotation, float movementSpeed);
        virtual ~TankShell();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->m_sprite.getGlobalBounds(); }

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
