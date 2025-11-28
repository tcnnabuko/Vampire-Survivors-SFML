#include "Player.h"
#include <cmath>

static sf::Vector2f normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x*v.x + v.y*v.y);
    if (len != 0) v /= len;
    return v;
}

Player::Player()
{
    shape.setRadius(15);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(15,15);
    shape.setPosition(640,360);
}

void Player::update(float dt)
{
    hp += regenRate * dt;
    if (hp > maxHp) hp = maxHp;

    sf::Vector2f dir{0,0};

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1;

    dir = normalize(dir);
    shape.move(dir * (speed+bonusSpeed) * dt);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(shape);
}

bool Player::canShoot()
{
    return shootTimer.getElapsedTime().asSeconds() >= fireRate;
}

void Player::resetShootTimer()
{
    shootTimer.restart();
}

void Player::addXP(int amount)
{
    xp += amount;
    if (xp >= nextLevel)
    {
        xp = 0;
        level++;
        nextLevel += 5;
        levelUpPending = true;
    }
}

void Player::chooseUpgrade(int option)
{
    if (option == 1)
    {
        pierceLevel++;
        weapon = pierceLevel >= 5 ? WeaponType::PIERCING_EVOLVED : WeaponType::PIERCING;
    }
    if (option == 2)
    {
        tripleLevel++;
        weapon = tripleLevel >= 5 ? WeaponType::TRIPLE_EVOLVED : WeaponType::TRIPLE;
    }
    if (option == 3)
    {
        orbitLevel++;
        weapon = orbitLevel >= 5 ? WeaponType::ORBITAL_EVOLVED : WeaponType::ORBITAL;
    }
    levelUpPending = false;
}

void Player::addPassive(PassiveType type)
{
    for (auto& p : passives)
        if (p.type == type)
        {
            p.level++;
            if (type == PassiveType::DAMAGE) bonusDamage += 0.3f;
            if (type == PassiveType::SPEED) bonusSpeed += 15;
            if (type == PassiveType::MAGNET) magnetRange += 20;
            if (type == PassiveType::REGEN) regenRate += 0.4f;
            if (type == PassiveType::ARMOR) armor += 1;
            return;
        }

    passives.push_back({type,1});
    if (type == PassiveType::DAMAGE) bonusDamage += 1;
    if (type == PassiveType::SPEED) bonusSpeed += 30;
    if (type == PassiveType::MAGNET) magnetRange += 40;
    if (type == PassiveType::REGEN) regenRate += 1;
    if (type == PassiveType::ARMOR) armor += 2;
}

void Player::takeDamage(float dmg)
{
    dmg -= armor;
    if (dmg < 1) dmg = 1;
    hp -= dmg;
}

sf::Vector2f Player::getPosition()
{
    return shape.getPosition();
}

sf::FloatRect Player::getBounds()
{
    return shape.getGlobalBounds();
}
