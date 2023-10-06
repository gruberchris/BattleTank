//
// Created by Christopher Gruber on 9/19/23.
//

#include "TankShell.h"

namespace battletank {
        TankShell::TankShell(const sf::Texture* texture, float posX, float posY, float dirX, float dirY, float rotation, float movementSpeed) : m_movementSpeed(movementSpeed) {
            this->m_sprite.setTexture(*texture);
            this->m_sprite.scale(0.5f, 0.5f);
            this->m_sprite.setOrigin(this->m_sprite.getLocalBounds().width / 2.f, this->m_sprite.getLocalBounds().height / 2.f);
            this->m_sprite.setPosition(posX, posY);
            this->m_sprite.setRotation(rotation);

            this->m_direction.x = dirX;
            this->m_direction.y = dirY;
        }

        TankShell::~TankShell() {

        }

        void TankShell::update() {
            this->m_sprite.move(this->m_movementSpeed * this->m_direction.x, this->m_movementSpeed * this->m_direction.y);
        }

        void TankShell::render(sf::RenderTarget* target) {
            target->draw(this->m_sprite);
        }

    bool TankShell::isOutOfViewTop() {
        return this->m_sprite.getPosition().y + this->m_sprite.getGlobalBounds().height < 0.f;
    }

    bool TankShell::isOutOfViewBottom(sf::RenderTarget* target) {
        return this->getGlobalBounds().top > target->getSize().y;
    }

    bool TankShell::isOutOfViewLeft() {
        return this->getGlobalBounds().left +this->getGlobalBounds().width < 0.f;
    }

    bool TankShell::isOutOfViewRight(sf::RenderTarget* target) {
        return this->getGlobalBounds().left > target->getSize().x;
    }

    bool TankShell::isOutOfView(sf::RenderTarget* target) {
        return this->isOutOfViewTop() || this->isOutOfViewBottom(target) || this->isOutOfViewLeft() || this->isOutOfViewRight(target);
    }
} // battletank