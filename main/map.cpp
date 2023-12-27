#include <SFML/Graphics.hpp>
#include "map.h"

void initializeMap(sf::RenderWindow &window)
{
    sf::Texture mapTexture;
    mapTexture.loadFromFile("D:/2ndCourse/cPlus/myGame/images/map/level1/whole_map.png");

    sf::Sprite map;
    map.setTexture(mapTexture);
    map.setPosition(0, 0);
    window.draw(map);
}