//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_ENEMYTANK_H
#define BATTLETANK_ENEMYTANK_H

#include <SFML/Graphics.hpp>

namespace battletank {

    class EnemyTank {
    private:
        int hitPoints = 0;
        int maxHitPoints = 10;
        int damage = 1;
        int points = 5;
        int type = 0;

        sf::Sprite hull_sprite;
        sf::Texture hull_texture;
        sf::Sprite turret_sprite;
        sf::Texture turret_texture;
        float movementSpeed = 0.5f;
        float rotationSpeed = 1.f;
        float attackCooldownMax = 10.f;
        float attackCooldown = 0.f;
        const float attackRateOfFire = 0.035f;

        // Methods
        void initSprite(const sf::Texture* hull_texture, const sf::Texture* turret_texture, float posX, float posY, float rotation);
        void setTexture(sf::Texture const* t) { this->hull_texture = *t; }
        sf::Texture getTexture() const { return this->hull_texture; }
        void setTurretTexture(sf::Texture const* t) { this->turret_texture = *t; }
        sf::Texture getTurretTexture() const { return this->turret_texture; }

    public:
        EnemyTank(sf::Texture* hull_texture, sf::Texture* turret_texture, float posX, float posY, float rotation);
        virtual ~EnemyTank();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->hull_sprite.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return this->hull_sprite.getPosition(); }
        float getRotation() const { return this->hull_sprite.getRotation(); }
        sf::Vector2f getOrigin() const { return this->hull_sprite.getOrigin(); }
        sf::FloatRect getBoundingBox() const { return this->hull_sprite.getGlobalBounds(); }

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
