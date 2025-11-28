#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Weapon.h"
#include "Passive.h"

class Player
{
private:
    sf::CircleShape shape;
    float speed = 220.f;

    int level = 1;
    int xp = 0;
    int nextLevel = 5;

    sf::Clock shootTimer;
    float fireRate = 0.5f;

    WeaponType weapon = WeaponType::BASIC;

    int tripleLevel = 0;
    int pierceLevel = 0;
    int orbitLevel = 0;

    bool levelUpPending = false;

public:
    float hp = 100;
    float maxHp = 100;
    float regenRate = 0;
    float bonusSpeed = 0;
    float bonusDamage = 1;
    float magnetRange = 80;
    float armor = 0;

    std::vector<Passive> passives;

    Player();

    void update(float dt);
    void draw(sf::RenderWindow& window);

    bool canShoot();
    void resetShootTimer();

    void addXP(int amount);
    void chooseUpgrade(int option);
    void addPassive(PassiveType type);
    void takeDamage(float dmg);

    bool canLevelUp() const { return levelUpPending; }

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();

    float getHPPercent() const { return hp / maxHp; }
    float getMagnetRange() const { return magnetRange; }
    WeaponType getWeapon() const { return weapon; }
};
