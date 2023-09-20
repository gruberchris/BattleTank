//
// Created by Christopher Gruber on 9/19/23.
//

#include "TankShell.h"

namespace battletank {
        TankShell::TankShell() {
            this->sprite.setPosition(0.f, 0.f);
            this->sprite.setScale(0.1f, 0.1f);
            this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);
        }

        TankShell::TankShell(const sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed) {
            this->sprite.setTexture(*texture);
            this->sprite.setPosition(posX, posY);
            this->sprite.setScale(0.1f, 0.1f);
            this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2.f, this->sprite.getGlobalBounds().height / 2.f);

            this->direction.x = dirX;
            this->direction.y = dirY;
            this->movementSpeed = movementSpeed;
        }

        TankShell::~TankShell() {

        }

        void TankShell::update() {
            this->sprite.move(this->movementSpeed * this->direction);
        }

        void TankShell::render(sf::RenderTarget* target) {
            target->draw(this->sprite);
        }
} // battletank