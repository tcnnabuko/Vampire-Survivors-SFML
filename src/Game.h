#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "XP.h"
#include "UpgradeMenu.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock dtClock;
    sf::Clock enemySpawnClock;

    sf::View camera;
    sf::Font font;

    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<XP> gems;

    UpgradeMenu upgradeMenu;
    bool menuActive = false;

    void handleEvents();
    void update(float dt);
    void render();

    void spawnEnemy();
    void handleCollisions();

public:
    Game();
    void run();
};
