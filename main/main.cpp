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
    Enemy enemySpear1;
    Enemy enemyBow1;
    Enemy enemySpear2;
    Enemy enemyBow2;
    int enemyNum = 4;

    Arrow arrow1;
    Arrow arrow2;
    Bullet bullet;

    hero.type = 2;
    initializeHero(hero);
    initializeEnemySpear(enemySpear1);
    initializeEnemySpear(enemySpear2);
    initializeEnemyBow(enemyBow1);
    initializeEnemyBow(enemyBow2);

    enemySpear1.sprite.setPosition(300, 300);
    enemySpear2.sprite.setPosition(800, 800);
    enemyBow1.sprite.setPosition(300, 800);
    enemyBow2.sprite.setPosition(800, 300);

    sf::Clock clock;
    sf::Clock clock2;

    bool isGame = true;
    float enemyFrame = 0;
    float enemyStandFrame = 0;
    float heroFrame = 0;

    while (window.isOpen())
    {
        redrawFrame(window);
        if (isGame == true)
        {
            move(hero, enemySpear1, heroFrame, clock);
            move(hero, enemyBow1, heroFrame, clock);
            move(hero, enemySpear2, heroFrame, clock);
            move(hero, enemyBow2, heroFrame, clock);
            enemyAnimationStand(enemySpear1, enemyStandFrame, clock2);
            enemyAnimationStand(enemyBow1, enemyStandFrame, clock2);
            enemyAnimationStand(enemySpear2, enemyStandFrame, clock2);
            enemyAnimationStand(enemyBow2, enemyStandFrame, clock2);
            enemyReaction(hero, enemySpear1, enemyFrame, window, arrow1);
            enemyReaction(hero, enemyBow1, enemyFrame, window, arrow1);
            enemyReaction(hero, enemySpear2, enemyFrame, window, arrow2);
            enemyReaction(hero, enemyBow2, enemyFrame, window, arrow2);
            heroAttack(hero, enemySpear1, bullet, window, clock);
            heroAttack(hero, enemyBow1, bullet, window, clock);
            heroAttack(hero, enemySpear2, bullet, window, clock);
            heroAttack(hero, enemyBow2, bullet, window, clock);
        }
        pollEvents(window);
        window.draw(enemySpear1.sprite);
        window.draw(enemyBow1.sprite);
        // window.draw(enemySpear2.sprite);
        // window.draw(enemyBow2.sprite);
        window.draw(hero.sprite);
        hpPanel(window, hero, isGame, enemyNum);
        window.display();
    }
}
