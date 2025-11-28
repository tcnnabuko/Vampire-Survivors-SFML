#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"

class Bullet
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    WeaponType type;
    int pierce = 1;
    float orbitAngle = 0;
    float orbitRadius = 60;

public:
    Bullet(sf::Vector2f pos, sf::Vector2f dir, WeaponType t);

    void update(float dt, sf::Vector2f playerPos);
    void draw(sf::RenderWindow& window);
    bool reducePierce() { return --pierce <= 0; }

    sf::FloatRect getBounds();
};
