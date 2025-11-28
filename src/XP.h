#pragma once
#include <SFML/Graphics.hpp>

class XP
{
private:
    sf::CircleShape shape;

public:
    XP(float x, float y);

    void update(float dt, sf::Vector2f playerPos, float magnet);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds();
};
