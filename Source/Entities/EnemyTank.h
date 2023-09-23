//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_ENEMYTANK_H
#define BATTLETANK_ENEMYTANK_H

#include<SFML/Graphics.hpp>

namespace battletank {

    class EnemyTank {
    private:
        int hitPoints = 0;
        int maxHitPoints = 10;
        int damage = 1;
        int points = 5;
        int type = 0;

        sf::Sprite sprite;
        sf::Texture texture;
        //sf::Vector2f direction;
        float movementSpeed = 0.5f;
        float rotationSpeed = 1.f;
        float attackCooldownMax = 10.f;
        float attackCooldown = 0.f;
        const float attackRateOfFire = 0.035f;

        // Methods
        void initTexture();
        void initSprite();

    public:
        EnemyTank(float posX, float posY);
        virtual ~EnemyTank();

        // Accessors
        sf::FloatRect getGlobalBounds() const { return this->sprite.getGlobalBounds(); }
        sf::Vector2f getPosition() const { return this->sprite.getPosition(); }

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
