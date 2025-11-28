#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(1280,720), "Vampire SFML")
{
    window.setFramerateLimit(60);
    camera = window.getDefaultView();
    font.loadFromFile("assets/arial.ttf");
}

void Game::run()
{
    while (window.isOpen())
    {
        float dt = dtClock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void Game::handleEvents()
{
    sf::Event e;
    while (window.pollEvent(e))
        if (e.type == sf::Event::Closed)
            window.close();

    if (menuActive)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
        { player.chooseUpgrade(upgradeMenu.options[0]); menuActive=false; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
        { player.chooseUpgrade(upgradeMenu.options[1]); menuActive=false; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
        { player.chooseUpgrade(upgradeMenu.options[2]); menuActive=false; }
    }
}

void Game::update(float dt)
{
    player.update(dt);

    camera.setCenter(player.getPosition());
    window.setView(camera);

    if (enemySpawnClock.getElapsedTime().asSeconds() > 0.8f)
    {
        spawnEnemy();
        enemySpawnClock.restart();
    }

    for (auto& e : enemies)
        e.update(player.getPosition(), dt);

    if (player.canShoot() && !enemies.empty())
    {
        sf::Vector2f dir = enemies[0].getPosition() - player.getPosition();
        if (player.getWeapon() == WeaponType::TRIPLE || player.getWeapon() == WeaponType::TRIPLE_EVOLVED)
        {
            bullets.emplace_back(player.getPosition(), dir, player.getWeapon());
            bullets.emplace_back(player.getPosition(), dir + sf::Vector2f(0.3f,0), player.getWeapon());
            bullets.emplace_back(player.getPosition(), dir - sf::Vector2f(0.3f,0), player.getWeapon());
        }
        else bullets.emplace_back(player.getPosition(), dir, player.getWeapon());

        player.resetShootTimer();
    }

    for (auto& b : bullets)
        b.update(dt, player.getPosition());

    for (auto& g : gems)
        g.update(dt, player.getPosition(), player.getMagnetRange());

    if (player.canLevelUp() && !menuActive)
    {
        upgradeMenu.roll();
        menuActive = true;
    }

    handleCollisions();
}

void Game::spawnEnemy()
{
    float y = rand()%800;
    int r = rand()%40;
    if (r==0) enemies.emplace_back(0,y,true,false);
    else if (r<5) enemies.emplace_back(0,y,false,true);
    else enemies.emplace_back(0,y);
}

void Game::handleCollisions()
{
    for (int i=0;i<enemies.size();i++)
    {
        for (int j=0;j<bullets.size();j++)
            if (enemies[i].getBounds().intersects(bullets[j].getBounds()))
            {
                enemies[i].takeHit(1 * player.bonusDamage);

                if (bullets[j].reducePierce())
                    bullets.erase(bullets.begin()+j);

                if (enemies[i].isDead())
                {
                    if(enemies[i].isBossEnemy())
                        player.addPassive((PassiveType)(rand()%5));

                    auto p=enemies[i].getPosition();
                    for(int k=0;k<6;k++)
                        gems.emplace_back(p.x+rand()%10,p.y+rand()%10);

                    enemies.erase(enemies.begin()+i);
                    break;
                }
            }
    }

    for(int i=0;i<gems.size();i++)
        if(gems[i].getBounds().intersects(player.getBounds()))
        {
            player.addXP(1);
            gems.erase(gems.begin()+i);
        }
}

void Game::render()
{
    window.clear(sf::Color(20,20,20));

    player.draw(window);
    for(auto&e:enemies)e.draw(window);
    for(auto&b:bullets)b.draw(window);
    for(auto&g:gems)g.draw(window);

    // Health bar
    sf::RectangleShape back({80,10});
    back.setFillColor(sf::Color::Red);
    back.setPosition(player.getPosition()+sf::Vector2f(-40,-40));

    sf::RectangleShape front({80*player.getHPPercent(),10});
    front.setFillColor(sf::Color::Green);
    front.setPosition(back.getPosition());

    window.draw(back);
    window.draw(front);

    // Upgrade menu
    if (menuActive)
    {
        sf::RectangleShape bg({500,200});
        bg.setPosition(player.getPosition() - sf::Vector2f(250,100));
        bg.setFillColor(sf::Color(0,0,0,200));
        window.draw(bg);

        for(int i=0;i<3;i++)
        {
            sf::Text t(std::to_string(i+1)+" - "+upgradeMenu.getText(upgradeMenu.options[i]),
                     font,22);
            t.setPosition(bg.getPosition()+sf::Vector2f(20,20+i*50));
            window.draw(t);
        }
    }

    window.display();
}
