#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include "map.h"
#include "fight.h"

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        defaut:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window)
{
    window.clear();
    initializeMap(window);
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1470; //1465
    constexpr unsigned WINDOW_HEIGHT = 988; //986

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Redeemer",
        sf::Style::Default, settings);

    Hero hero;
    Enemy enemySpear;
    Enemy enemyBow;
    int enemyNum = 2;

    Arrow arrow;
    Bullet bullet;

    hero.type = 1;
    initializeHero(hero);
    initializeEnemySpear(enemySpear);
    initializeEnemyBow(enemyBow);

    enemySpear.sprite.setPosition(300, 300);
    enemyBow.sprite.setPosition(800, 300);

    sf::Clock clock;

    bool isGame = true;
    float enemyFrame = 0;
    float enemyStandFrame = 0;
    float heroFrame = 0;

    while (window.isOpen())
    {
        redrawFrame(window);
        if (isGame == true)
        {
            move(hero, enemySpear, heroFrame, clock);
            move(hero, enemyBow, heroFrame, clock);
            enemyAnimationStand(enemySpear, enemyStandFrame);
            enemyAnimationStand(enemyBow, enemyStandFrame);
            enemyReaction(hero, enemySpear, enemyFrame, window, arrow);
            enemyReaction(hero, enemyBow, enemyFrame, window, arrow);
            heroAttack(hero, enemySpear, bullet, window, clock);
            heroAttack(hero, enemyBow, bullet, window, clock);
        }
        pollEvents(window);
        window.draw(enemySpear.sprite);
        window.draw(enemyBow.sprite);
        window.draw(hero.sprite);
        hpPanel(window, hero, isGame, enemyNum);
        window.display();
    }
}
