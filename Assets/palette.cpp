#include "palette.h"


// Mapped tile data to a specific pair of colors
const std::map<char, std::pair<sf::Color, sf::Color>> palette::colors = {
    {'*', std::make_pair(sf::Color(0xbdbdbdff), sf::Color(0x8d8d8dff))},
    {'0', std::make_pair(sf::Color(0xec407aff), sf::Color(0xb4004eff))},
    {'1', std::make_pair(sf::Color(0x9c27b0ff), sf::Color(0x6a0080ff))},
    {'2', std::make_pair(sf::Color(0x00bcd4ff), sf::Color(0x008ba3ff))},
    {'3', std::make_pair(sf::Color(0x009688ff), sf::Color(0x00675bff))},
    {'4', std::make_pair(sf::Color(0x4caf50ff), sf::Color(0x087f23ff))},
    {'5', std::make_pair(sf::Color(0xffee58ff), sf::Color(0xc9bc1fff))},
    {'6', std::make_pair(sf::Color(0x607d8bff), sf::Color(0x34515eff))},
    {'7', std::make_pair(sf::Color(0x8d6e63ff), sf::Color(0x5f4339ff))},
    {'8', std::make_pair(sf::Color(0xc62828ff), sf::Color(0x8e0000ff))},
    {'9', std::make_pair(sf::Color(0xe4e65eff), sf::Color(0x7c8500ff))},
    {'!', std::make_pair(sf::Color(0x2196f3ff), sf::Color(0x0069c0ff))}     
};


palette::palette (sf::RenderWindow& window)
{
   firaCode.loadFromFile("Fonts/FiraCode-Regular.woff"); 

}


void draw (char currentPaletteData, sf::RenderWindow& window)
{
    
}