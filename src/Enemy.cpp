#include "Enemy.h"
#include <cmath>

static sf::Vector2f normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x*v.x + v.y*v.y);
    if (len != 0) v /= len;
    return v;
}

Enemy::Enemy(float x, float y, bool isBoss, bool isElite)
: boss(isBoss), elite(isElite)
{
    shape.setSize({25,25});
    shape.setOrigin(12.5f,12.5f);
    shape.setPosition(x,y);

    if (boss)
    {
        shape.setSize({80,80});
        shape.setFillColor(sf::Color::Yellow);
        hp = 200;
        speed = 40;
    }
    else if (elite)
    {
        shape.setFillColor(sf::Color(255,100,100));
        hp = 15;
        speed = 130;
    }
    else
    {
        shape.setFillColor(sf::Color::Red);
        hp = 3;
    }
}

void Enemy::update(sf::Vector2f target, float dt)
{
    shape.move(normalize(target - shape.getPosition()) * speed * dt);
}

void Enemy::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

void Enemy::takeHit(float dmg)
{
    hp -= dmg;
}

sf::FloatRect Enemy::getBounds() { return shape.getGlobalBounds(); }
sf::Vector2f Enemy::getPosition() { return shape.getPosition(); }
