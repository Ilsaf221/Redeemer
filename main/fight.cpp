#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <windows.h>
#include "fight.h"

void victoryScene(sf::RenderWindow &window)
{
    sf::Texture victoryTexture;
    victoryTexture.loadFromFile("images/screen/gameOver/victory.png");

    sf::Sprite victory;
    victory.setTexture(victoryTexture);
    victory.setPosition(735, 494);
    victory.setOrigin(230, 128);
    window.draw(victory);
}

void gameOverScene(sf::RenderWindow &window)
{
    sf::Texture gameOverTexture;
    gameOverTexture.loadFromFile("images/screen/gameOver/gameOver.png");

    sf::Sprite gameOver;
    gameOver.setTexture(gameOverTexture);
    gameOver.setPosition(735, 494);
    gameOver.setOrigin(230, 128);
    window.draw(gameOver);
}

bool unitsCross(Hero &hero, Enemy &enemy)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    const sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const sf::Vector2f heroOrigin = hero.sprite.getOrigin();
    const sf::Vector2f enemyOrigin = enemy.sprite.getOrigin();

    if ((((heroPosition.y + 0.15 * heroOrigin.y / 2 >= enemyPosition.y - 0.16 * enemyOrigin.x) &&
          (heroPosition.y - 0.15 * heroOrigin.y / 2 <= enemyPosition.y + 0.16 * enemyOrigin.x)) &&
         ((heroPosition.x + 0.15 * heroOrigin.x >= enemyPosition.x - 0.16 * enemyOrigin.x) &&
          (heroPosition.x - 0.15 * heroOrigin.x <= enemyPosition.x + 0.16 * enemyOrigin.x))) &&
        (enemy.alive == true))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void enemyAnimationStand(Enemy &enemy, float &frame)
{
    if (enemy.alive == true)
    {
        if (enemy.type == 1)
        {
            enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimationStand.png");
        }
        else if (enemy.type == 2)
        {
            enemy.texture.loadFromFile("images/enemiesModels/animation/goblinBowAnimationStand.png");
        }
        else
        {
            enemy.texture.loadFromFile("images/enemiesModels/animation/goblinGunAnimationStand.png");
        }

        frame += 0.38;

        if (frame > 8)
        {
            frame -= 8;
        }

        enemy.sprite.setTextureRect(sf::IntRect(611 * int(frame), 0, 611, 590));
    }
}

void enemyAnimation(Enemy &enemy, float &frame)
{
    if (enemy.type == 1)
    {
        enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimation.png");
    }
    else if (enemy.type == 2)
    {
        enemy.texture.loadFromFile("images/enemiesModels/animation/goblinBowAnimation.png");
    }
    else
    {
        enemy.texture.loadFromFile("images/enemiesModels/animation/goblinGunAnimation.png");
    }

    frame += 0.07;

    if (frame > 2)
    {
        frame -= 2;
    }

    enemy.sprite.setTextureRect(sf::IntRect(611 * int(frame), 0, 611, 590));
}

void enemyMove(Enemy &enemy, float &frame, sf::Clock &clock)
{
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const float offsetX = -5 + (rand() % 11);
    const float offsetY = -5 + (rand() % 11);

    enemyPosition.x += offsetX;
    enemyPosition.y += offsetY;

    enemyAnimation(enemy, frame);
    enemy.sprite.setPosition(enemyPosition);
}

void enemySpearAttack(Enemy &enemy, Hero &hero)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    if (((heroPosition.y + 0.15 * 167.5 >= enemyPosition.y - 0.16 * 255) && (heroPosition.y - 0.15 * 167.5 <= enemyPosition.y + 0.16 * 255)) && ((heroPosition.x + 0.15 * 164 >= enemyPosition.x - 0.16 * 312) && (heroPosition.x - 0.15 * 164 <= enemyPosition.x + 0.16 * 312)))
    {
        enemy.sprite.setTextureRect(sf::IntRect(2 * 611, 0, 611, 590));
        hero.sprite.setColor(sf::Color(217, 124, 121));
        if (enemy.sprite.getScale().x >= 0)
        {
            hero.sprite.setPosition(heroPosition.x + 20, heroPosition.y);
        }
        else
        {
            hero.sprite.setPosition(heroPosition.x - 20, heroPosition.y);
        }
        if (hero.shield == false)
        {
            hero.hp -= 1;
        }
        else
        {
            hero.hp -= 0.3;
        }
    }
}

void initializeArrow(Arrow &arrow)
{
    arrow.texture.loadFromFile("images/enemiesModels/goblinBowSprites/arrow.png");
    arrow.sprite.setTexture(arrow.texture);
    arrow.sprite.setOrigin(330, 51);
    arrow.sprite.setScale(0.15f, 0.15f);
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateRotation(Arrow &arrow, const sf::Vector2f &heroPosition, sf::Vector2f &arrowPosition)
{
    const sf::Vector2f delta = heroPosition - arrowPosition;
    const float angle = atan2(delta.y, delta.x);
    arrow.sprite.setRotation(toDegrees(angle));
}

void yodaAbility(Hero &hero, Arrow &arrow)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    const sf::Vector2f arrowPosition = arrow.sprite.getPosition();

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)))
    {
        hero.sprite.setTextureRect(sf::IntRect(4 * 649, 0, 721, 649));

        if (((((heroPosition.y + 0.15 * 167 >= arrowPosition.y) &&
               (heroPosition.y - 0.15 * 137 <= arrowPosition.y)) &&
              ((heroPosition.x + 0.15 * 169 <= arrowPosition.x) &&
               (heroPosition.x + 0.15 * 426 >= arrowPosition.x))) &&
             (hero.sprite.getScale().x >= 0)) ||
            ((((heroPosition.y + 0.15 * 167 >= arrowPosition.y) &&
               (heroPosition.y - 0.15 * 137 <= arrowPosition.y)) &&
              ((heroPosition.x - 0.15 * 169 >= arrowPosition.x) &&
               (heroPosition.x - 0.15 * 426 < arrowPosition.x))) &&
             (hero.sprite.getScale().x <= 0)))
        {
            arrow.direction = -arrow.direction;
            arrow.reflected = true;
            arrow.sprite.setScale(-0.15f, 0.15f);
        }
    }
}

void grootAbility(Hero &hero, sf::RenderWindow &window)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();

    if ((sf::Mouse::isButtonPressed(sf::Mouse::Right)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)))
    {

        sf::Texture shieldTexture;
        sf::Sprite shield;

        shieldTexture.loadFromFile("images/heroesModels/grootSprites/woodShield.png");
        shield.setTexture(shieldTexture);
        shield.setScale(0.15f, 0.15f);
        shield.setOrigin(153, 250);

        if (hero.sprite.getScale().x >= 0)
        {
            shield.setPosition(heroPosition.x + 20, heroPosition.y);
        }
        else
        {
            shield.setPosition(heroPosition.x - 20, heroPosition.y);
        }

        hero.shield = true;
        window.draw(shield);
    }
    else
    {
        hero.shield = false;
    }
}

void arrowState(Hero &hero, Enemy &enemy, Arrow &arrow)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    const sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const sf::Vector2f arrowPosition = arrow.sprite.getPosition();

    if (((heroPosition.y + 0.15 * 167.5 >= arrowPosition.y) &&
         (heroPosition.y - 0.15 * 167.5 <= arrowPosition.y)) &&
        ((heroPosition.x + 0.15 * 164 >= arrowPosition.x) &&
         (heroPosition.x - 0.15 * 164 <= arrowPosition.x)))
    {

        arrow.move = false;
        arrow.hit = true;
        if (hero.shield == false)
        {
            hero.sprite.setColor(sf::Color(217, 124, 121));
            hero.hp -= 1;
        }
    }

    if ((((arrowPosition.y >= enemyPosition.y - 0.16 * 255) &&
          (arrowPosition.y <= enemyPosition.y + 0.16 * 255)) &&
         ((arrowPosition.x >= enemyPosition.x - 0.16 * 312) &&
          (arrowPosition.x <= enemyPosition.x + 0.16 * 312))) &&
        arrow.reflected == true)
    {
        arrow.move = false;
        arrow.hit = true;
        enemy.sprite.setColor(sf::Color(217, 124, 121));
        enemy.hp -= 2.5;
        arrow.reflected = false;
    }

    if (((arrowPosition.y <= 44.675) || (arrowPosition.y >= 940.325) || (arrowPosition.x <= 48) || (arrowPosition.x >= 1405.8)) || (enemy.move == false))
    {
        arrow.move = false;
        arrow.hit = true;
    }
}

void enemyBowAttack(Enemy &enemy, Hero &hero, sf::RenderWindow &window, Arrow &arrow)
{
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const sf::Vector2f heroPosition = hero.sprite.getPosition();

    if (arrow.move == false)
    {
        initializeArrow(arrow);
        arrow.sprite.setPosition(enemyPosition.x, enemyPosition.y);
        updateRotation(arrow, heroPosition, enemyPosition);
        arrow.hit = false;
        enemy.sprite.setColor(sf::Color(255, 255, 255));
    }

    sf::Vector2f arrowPosition = arrow.sprite.getPosition();

    if (hero.type == 1)
    {
        yodaAbility(hero, arrow);
    }
    else if (hero.type == 2)
    {
        grootAbility(hero, window);
    }

    arrowState(hero, enemy, arrow);

    if ((arrowPosition.x - enemyPosition.x == 200) && (arrowPosition.y - enemyPosition.y == 200))
    {
        arrow.hit = true;
    }

    if (arrow.hit == false)
    {

        const float speed = 15;

        if (arrow.move == false)
        {
            const sf::Vector2f motion = heroPosition - arrowPosition;
            if (arrow.reflected == false)
            {
                arrow.direction = {(double)motion.x / sqrt(pow((double)motion.x, 2) + pow((double)motion.y, 2)),
                                   (double)motion.y / sqrt(pow((double)motion.x, 2) + pow((double)motion.y, 2))};
            }
            arrow.move = true;
        }

        arrowPosition = arrowPosition + arrow.direction * speed;

        arrow.sprite.setPosition(arrowPosition);

        window.draw(arrow.sprite);
    }
}

void enemyReaction(Hero &hero, Enemy &enemy, float &frame, sf::RenderWindow &window, Arrow &arrow)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();

    const float step = 3;

    const sf::Vector2f motion = heroPosition - enemyPosition;

    if ((abs(motion.x) <= 70) && (abs(motion.y) <= 70))
    {
        enemy.move = true;
    }

    sf::Vector2f direction;
    if (enemy.hp <= 0)
    {
        direction = {0, 0};
        enemy.sprite.setColor(sf::Color(94, 93, 88));
        enemy.sprite.setRotation(-90);
        enemy.alive = false;
    }
    else
    {

        enemyAnimation(enemy, frame);
        if (enemy.move == true)
        {
            if (enemy.type == 1)
            {
                if ((abs(motion.x <= 300) && abs(motion.y <= 300)) && (enemy.move == true))
                {
                    direction = {motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2)),
                                 motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2))};
                    enemySpearAttack(enemy, hero);
                }
            }
            else if (enemy.type == 2)
            {
                if ((abs(motion.x) <= 150) && (abs(motion.y) <= 150))
                {
                    direction = {-motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2)),
                                 -motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2))};
                }
                enemyBowAttack(enemy, hero, window, arrow);
            }
        }

        if (motion.x < 0)
        {
            enemy.sprite.setScale(-0.16, 0.16);
        }
        else
        {
            enemy.sprite.setScale(0.16, 0.16);
        }
    }

    enemyPosition = enemyPosition + direction * step;
    enemy.sprite.setPosition(enemyPosition);
}

void initializebullet(Bullet &bullet, Hero &hero)
{
    if (hero.type == 2)
    {
        bullet.texture.loadFromFile("images/heroesModels/grootSprites/woodBall.png");
        bullet.sprite.setScale(0.25f, 0.25f);
    }
    else
    {
        bullet.texture.loadFromFile("images/heroesModels/spiderManSprites/web.png");
        bullet.sprite.setScale(0.5f, 0.5f);
    }
    bullet.sprite.setTexture(bullet.texture);
    bullet.sprite.setOrigin(55, 55);
}

void updatebulletRotation(Bullet &bullet, const sf::Event::MouseMoveEvent &event, const sf::Vector2f &heroPosition)
{
    const sf::Vector2f mousePosition;
    POINT mousePoint;
    if (GetCursorPos(&mousePoint))
    {

        sf::Vector2f mousePosition = {float(mousePoint.x),
                                      float(mousePoint.y)};
    }

    const sf::Vector2f delta = mousePosition - heroPosition;
    const float angle = atan2(delta.y, delta.x);
    bullet.sprite.setRotation(toDegrees(angle));
}

void bulletState(Hero &hero, Enemy &enemy, Bullet &bullet)
{
    const sf::Vector2f heroPosition = hero.sprite.getPosition();
    const sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const sf::Vector2f bulletPosition = bullet.sprite.getPosition();

    if (((bulletPosition.y >= enemyPosition.y - 0.16 * 255) &&
         (bulletPosition.y <= enemyPosition.y + 0.16 * 255)) &&
        ((bulletPosition.x >= enemyPosition.x - 0.16 * 312) &&
         (bulletPosition.x <= enemyPosition.x + 0.16 * 312)))
    {

        bullet.move = false;
        bullet.hit = true;
        if (hero.type == 2)
        {
            enemy.hp -= 2;
            if (enemy.hp <= 0)
            {
                enemy.alive = false;
            }
            if (enemy.alive == true)
            {
                enemy.sprite.setColor(sf::Color(217, 124, 121));
            }
        }
        else
        {
            enemy.move = false;
            enemy.sprite.setColor(sf::Color(190, 194, 196));
        }
    }

    if ((bulletPosition.y <= 44.675) || (bulletPosition.y >= 940.325) || (bulletPosition.x <= 48) || (bulletPosition.x >= 1405.8))
    {
        bullet.move = false;
        bullet.hit = true;
    }
}

void bulletAttack(Enemy &enemy, Hero &hero, sf::RenderWindow &window, Bullet &bullet)
{
    sf::Vector2f enemyPosition = enemy.sprite.getPosition();
    const sf::Vector2f heroPosition = hero.sprite.getPosition();

    if ((bullet.move == false) &&
        (((((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))) && (hero.type == 2)) ||
         ((((sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))) && (hero.type == 3))))
    {
        sf::Event event;

        initializebullet(bullet, hero);
        bullet.sprite.setPosition(heroPosition.x, heroPosition.y);
        updatebulletRotation(bullet, event.mouseMove, heroPosition);
        bullet.hit = false;
    }

    sf::Vector2f bulletPosition = bullet.sprite.getPosition();

    bulletState(hero, enemy, bullet);

    if (bullet.hit == false)
    {

        // const sf::Vector2f speed = 10;

        if (bullet.move == false)
        {
            // sf::Vector2f motion;
            // POINT mousePoint;
            // if (GetCursorPos(&mousePoint))
            // {

            //     const sf::Vector2f mousePosition = {float(mousePoint.x),
            //                                         float(mousePoint.y)};
            //     motion = mousePosition - heroPosition;
            // }

            // bullet.direction = {(double)motion.x / sqrt(pow((double)motion.x, 2) + pow((double)motion.y, 2)),
            //                   (double)motion.y / sqrt(pow((double)motion.x, 2) + pow((double)motion.y, 2))};

            if (hero.sprite.getScale().x >= 0)
            {
                bullet.direction = {10, 0};
            }
            else
            {
                bullet.direction = {-10, 0};
            }

            bullet.move = true;
        }

        bulletPosition = bulletPosition + bullet.direction;

        bullet.sprite.setPosition(bulletPosition);

        window.draw(bullet.sprite);
    }
}

void heroAttack(Hero &hero, Enemy &enemy, Bullet &Bullet, sf::RenderWindow &window, sf::Clock &clock)
{

    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) || (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
    {
        if (hero.type == 1)
        {
            hero.sprite.setTextureRect(sf::IntRect(4 * 649, 0, 721, 649));
        }
        else if (hero.type == 3)
        {
            hero.sprite.setTextureRect(sf::IntRect(4 * 472, 0, 472, 649));
        }

        const sf::Vector2f heroPosition = hero.sprite.getPosition();
        const sf::Vector2f enemyPosition = enemy.sprite.getPosition();

        if (unitsCross(hero, enemy) == true)
        {
            enemy.sprite.setColor(sf::Color(217, 124, 121));
            if (hero.sprite.getScale().x >= 0)
            {
                enemy.sprite.setPosition(enemyPosition.x + 10, enemyPosition.y);
            }
            else
            {
                enemy.sprite.setPosition(enemyPosition.x - 10, enemyPosition.y);
            }
            enemy.hp -= 1;
        }
    }
    if (hero.type == 2)
    {
        hero.sprite.setTextureRect(sf::IntRect(4 * 472, 0, 472, 708));
        bulletAttack(enemy, hero, window, Bullet);
    }
    else if (hero.type == 3)
    {
        bulletAttack(enemy, hero, window, Bullet);
    }
}

void heroAnimation(Hero &hero, float &frame, sf::Clock &clock)
{
    float time = clock.getElapsedTime().asMicroseconds();
    time = time / 800;

    frame += 0.0021 * time;
    if (frame > 4)
    {
        frame -= 4;
        clock.restart();
    }

    switch (hero.type)
    {
    case 1:
        hero.sprite.setTextureRect(sf::IntRect(649 * int(frame), 0, 649, 649));
        break;
    case 2:
        hero.sprite.setTextureRect(sf::IntRect(472 * int(frame), 0, 472, 708));
        break;
    case 3:
        hero.sprite.setTextureRect(sf::IntRect(472 * int(frame), 0, 472, 649));
        break;
    }
}

void move(Hero &hero, Enemy &enemy, float frame, sf::Clock &clock)
{
    sf::Vector2f heroPosition = hero.sprite.getPosition();
    sf::Vector2f enemyOrigin = enemy.sprite.getPosition();

    const float step = 5;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if (heroPosition.y - step >= 44.675)
        {
            heroPosition.y -= step;
        }
        hero.sprite.setColor(sf::Color(255, 255, 255));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if (heroPosition.y + step <= 887.325)
        {
            heroPosition.y += step;
        }
        hero.sprite.setColor(sf::Color(255, 255, 255));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if (heroPosition.x - step >= 64.2)
        {
            heroPosition.x -= step;
            hero.sprite.setScale(-0.15f, 0.15f);
        }
        hero.sprite.setColor(sf::Color(255, 255, 255));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if (heroPosition.x + step <= 1405.8)
        {
            heroPosition.x += step;
            hero.sprite.setScale(0.15f, 0.15f);
        }
        hero.sprite.setColor(sf::Color(255, 255, 255));
    }

    hero.sprite.setPosition(heroPosition);
    heroAnimation(hero, frame, clock);
}

void hpPanel(sf::RenderWindow &window, Hero &hero, bool &isGame, int &enemyNum)
{
    sf::Texture hpIcon;
    hpIcon.loadFromFile("images/screen/hp/hpPanel2.png");
    sf::Sprite hp;
    hp.setTexture(hpIcon);
    hp.setPosition(31, 30);
    hp.setOrigin(20.5, 30);
    hp.setTextureRect(sf::IntRect(0, 0, 41 * hero.hp, 60));

    sf::RectangleShape panelBG;
    panelBG.setSize({209, 50});
    panelBG.setPosition({8, 7});
    panelBG.setFillColor(sf::Color(168, 137, 93));
    panelBG.setOutlineColor(sf::Color(0x00, 0x00, 0x00));
    panelBG.setOutlineThickness(2);

    window.draw(panelBG);
    window.draw(hp);

    if (hero.hp <= 0)
    {
        isGame = false;
        gameOverScene(window);
    }

    if (hero.killed >= enemyNum)
    {
        victoryScene(window);
    }
}

void initializeEnemySpear(Enemy &enemy)
{
    enemy.texture.loadFromFile("images/enemiesModels/animation/goblinSpearAnimation.png");
    enemy.sprite.setTexture(enemy.texture);
    enemy.sprite.setOrigin(255, 312);
    enemy.sprite.setScale(
        0.16f,
        0.16f);
    enemy.sprite.setTextureRect(sf::IntRect(0, 0, 611, 590));
    enemy.type = 1;
}

void initializeEnemyBow(Enemy &enemy)
{
    enemy.texture.loadFromFile("images/enemiesModels/animation/goblinBowAnimation.png");
    enemy.sprite.setTexture(enemy.texture);
    // enemy.sprite.setPosition(900, 600);
    enemy.sprite.setOrigin(255, 312);
    enemy.sprite.setScale(
        0.16f,
        0.16f);
    enemy.sprite.setTextureRect(sf::IntRect(0, 0, 611, 590));
    enemy.type = 2;
}

void initializeYoda(Hero &hero)
{

    hero.texture.loadFromFile("images/heroesModels/animation/yodaAnimation.png");

    hero.sprite.setTexture(hero.texture);
    hero.sprite.setPosition(735, 494);
    hero.sprite.setOrigin(295, 324.5);
    hero.sprite.setScale(0.15f, 0.15f);
    hero.sprite.setTextureRect(sf::IntRect(0, 0, 649, 649));
}

void initializeGroot(Hero &hero)
{

    hero.texture.loadFromFile("images/heroesModels/animation/grootAnimation.png");

    hero.sprite.setTexture(hero.texture);
    hero.sprite.setPosition(735, 494);
    hero.sprite.setOrigin(174, 324.5);
    hero.sprite.setScale(0.15f, 0.15f);
    hero.sprite.setTextureRect(sf::IntRect(0, 0, 472, 708));
}

void initializeSpiderMan(Hero &hero)
{

    hero.texture.loadFromFile("images/heroesModels/animation/spiderManAnimation.png");

    hero.sprite.setTexture(hero.texture);
    hero.sprite.setPosition(735, 494);
    hero.sprite.setOrigin(236, 324.5);
    hero.sprite.setScale(0.15f, 0.15f);
    hero.sprite.setTextureRect(sf::IntRect(0, 0, 472, 649));
}

void initializeHero(Hero &hero)
{
    switch (hero.type)
    {
    case 1:
        initializeYoda(hero);
        break;
    case 2:
        initializeGroot(hero);
        break;
    case 3:
        initializeSpiderMan(hero);
        break;
    }
}
