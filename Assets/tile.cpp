#include "tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

extern std::map<char, std::pair<sf::Color, sf::Color>> palette;



char tile::getData () const
{
    return data;
}

float tile::getScale () const
{
    return scale;
}
