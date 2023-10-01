//
// Created by Christopher Gruber on 9/17/23.
//

#ifndef BATTLETANK_BASETANK_H
#define BATTLETANK_BASETANK_H

#include <SFML/Graphics.hpp>

namespace battletank {

    class BaseTank {
    private:
        int hit_points = 10;

    public:
        BaseTank();
        virtual ~BaseTank();

        // Accessors
        [[nodiscard]] int getHitPoints() const { return this->hit_points; }
        void setHitPoints(int hp) { this->hit_points = hp; }

        // Methods
        void takeDamage(int damage) { this->hit_points -= damage; }
        virtual void update() = 0;
    };

} // battletank

#endif //BATTLETANK_BASETANK_H
