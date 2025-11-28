#include "XP.h"
#include <cmath>

XP::XP(float x, float y)
{
    shape.setRadius(6);
    shape.setOrigin(6,6);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x,y);
}

void XP::update(float dt, sf::Vector2f p, float magnet)
{
    float dx = p.x - shape.getPosition().x;
    float dy = p.y - shape.getPosition().y;
    float d = std::sqrt(dx*dx + dy*dy);

    if (d < magnet)
        shape.move((dx/d) * 300 * dt, (dy/d) * 300 * dt);
}

void XP::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::FloatRect XP::getBounds()
{
    return shape.getGlobalBounds();
}
