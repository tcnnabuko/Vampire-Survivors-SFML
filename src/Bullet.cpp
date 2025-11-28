#include "Bullet.h"
#include <cmath>

static sf::Vector2f normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x*v.x + v.y*v.y);
    if (len != 0) v /= len;
    return v;
}

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f dir, WeaponType t)
: type(t)
{
    shape.setRadius(5);
    shape.setOrigin(5,5);
    velocity = normalize(dir) * 500.f;
    shape.setPosition(pos);

    if (t == WeaponType::PIERCING || t == WeaponType::PIERCING_EVOLVED)
    {
        pierce = (t == WeaponType::PIERCING_EVOLVED) ? 999 : 3;
        shape.setFillColor(sf::Color::Magenta);
    }
    else if (t == WeaponType::TRIPLE || t == WeaponType::TRIPLE_EVOLVED)
    {
        shape.setFillColor(sf::Color::Yellow);
        if (t == WeaponType::TRIPLE_EVOLVED) velocity *= 1.5f;
    }
    else if (t == WeaponType::ORBITAL || t == WeaponType::ORBITAL_EVOLVED)
    {
        shape.setFillColor(sf::Color::Cyan);
        if (t == WeaponType::ORBITAL_EVOLVED) orbitRadius = 110;
    }
    else shape.setFillColor(sf::Color::White);
}

void Bullet::update(float dt, sf::Vector2f playerPos)
{
    if (type == WeaponType::ORBITAL || type == WeaponType::ORBITAL_EVOLVED)
    {
        orbitAngle += 2 * dt;
        shape.setPosition(
            playerPos.x + std::cos(orbitAngle) * orbitRadius,
            playerPos.y + std::sin(orbitAngle) * orbitRadius
        );
    }
    else shape.move(velocity * dt);
}

void Bullet::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

sf::FloatRect Bullet::getBounds() { return shape.getGlobalBounds(); }
