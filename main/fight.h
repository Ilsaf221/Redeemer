#include <SFML/Graphics.hpp>

struct Hero
{
    sf::Texture texture;
    sf::Sprite sprite;
    int type;
    int hp = 5;
    int killed = 0;
    int shield = false;
};

struct Enemy
{
    sf::Texture texture;
    sf::Sprite sprite;
    int type;
    int hp = 5;
    bool alive = true;
    bool move = true;
};

struct Arrow
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f direction;
    bool hit = false;
    bool move = false;
    bool reflected = false;
};

struct Bullet
{
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f direction;
    bool hit = false;
    bool move = false;
};

void initializeHero(Hero &hero);
void initializeEnemySpear(Enemy &enemy);
void initializeEnemyBow(Enemy &enemy);
void initializeEnemyGun(Enemy &enemy);
void hpPanel(sf::RenderWindow &window, Hero &hero, bool &isGame, int &enemyNum);
void move(Hero &hero, Enemy &enemy, float frame, sf::Clock &clock);
void heroAnimation(Hero &hero, float &frame, sf::Clock &clock);
void heroAttack(Hero &hero, Enemy &enemy, Bullet &bullet, sf::RenderWindow &window, sf::Clock &clock);
void enemyReaction(Hero &hero, Enemy &enemy, float &frame, sf::RenderWindow &window, Arrow &arrow);
void enemyAttack(Enemy &enemy, Hero &hero);
void enemyMove(Enemy &enemy, float &frame, sf::Clock &clock);
void enemyAnimation(Enemy &enemy, float &frame);
void enemyAnimationStand(Enemy &enemy, float &frame);