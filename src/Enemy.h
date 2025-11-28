#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
    sf::RectangleShape shape;
    float speed = 90.f;
    float hp = 3;
    bool boss = false;
    bool elite = false;

public:
    Enemy(float x, float y, bool isBoss=false, bool isElite=false);

    void update(sf::Vector2f target, float dt);
    void draw(sf::RenderWindow& window);

    void takeHit(float dmg);
    bool isDead() const { return hp <= 0; }
    bool isBossEnemy() const { return boss; }

    sf::FloatRect getBounds();
    sf::Vector2f getPosition();
};
