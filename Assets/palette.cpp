#include <SFML/Graphics/RenderWindow.hpp>
#include "palette.h"
extern sf::RenderWindow window;


char Palette::currentData = '0';

// Mapped tile data to a specific pair of colors
const std::map<char, std::pair<sf::Color, sf::Color>> Palette::colors = {
    {'*', std::make_pair(sf::Color(0xbdbdbdff), sf::Color(0x8d8d8dff))},
    {'0', std::make_pair(sf::Color(0xec407aff), sf::Color(0xb4004eff))},
    {'1', std::make_pair(sf::Color(0x9c27b0ff), sf::Color(0x6a0080ff))},
    {'2', std::make_pair(sf::Color(0x00bcd4ff), sf::Color(0x008ba3ff))},
    {'3', std::make_pair(sf::Color(0x009688ff), sf::Color(0x00675bff))},
    {'4', std::make_pair(sf::Color(0x4caf50ff), sf::Color(0x087f23ff))},
    {'5', std::make_pair(sf::Color(0x607d8bff), sf::Color(0x34515eff))},
    {'6', std::make_pair(sf::Color(0x8d6e63ff), sf::Color(0x5f4339ff))},
    {'7', std::make_pair(sf::Color(0xc62828ff), sf::Color(0x8e0000ff))},
    {'!', std::make_pair(sf::Color(0x2196f3ff), sf::Color(0x0069c0ff))}     
};


Palette::Palette ():
    unit(window.getSize().y / 15.f),
    origin(0.f, (window.getSize().y - 10.f * Palette::unit) / 2.f)

{
    firaCode.loadFromFile("Fonts/FiraCode-Regular.woff"); 

    sf::Vector2f currentRectanglePos(origin);
    sf::Text fillerText;
    sf::RectangleShape fillerShape(sf::Vector2f(Palette::unit, Palette::unit));

    fillerText.setFont(firaCode);
    fillerText.setCharacterSize(25);
    fillerShape.setOutlineThickness(-4.f);
    
    for (char c : drawSequence) {
        const auto& color = Palette::colors.at(c);

        fillerText.setString(c);
        fillerText.setPosition(currentRectanglePos + sf::Vector2f(5.f, 5.f));

        fillerShape.setFillColor(color.first);
        fillerShape.setOutlineColor(color.second);
        fillerShape.setPosition(currentRectanglePos);
        
        shapeWithText.emplace_back(fillerShape, fillerText);
        currentRectanglePos += sf::Vector2f(0.f, Palette::unit);
    }
}


void Palette::draw ()
{
    int seq = 0;
    for (auto& it : shapeWithText) {
        char c = drawSequence[seq++];

        if(c == currentData)
            it.first.setOutlineColor(sf::Color(0xddddddff));
        else
            it.first.setOutlineColor(Palette::colors.at(c).second);

        window.draw(it.first);

        if (c != '*')
            window.draw(it.second);
    }
}


bool Palette::onPaletteClick ()
{
    // Calculating x, y co-ordinates relative to the origin of palette / colorGuide
    int x = sf::Mouse::getPosition().x - (int)origin.x,
        y = sf::Mouse::getPosition().y - (int)origin.y;
    
    x /= Palette::unit;
    y /= Palette::unit;

    // Bound Check to see which color is clicked on; if any
    if (x < 1 and y >= 0 and y < sizeof(drawSequence)) {
        currentData = (y == 0 ? '*' : y - 1 + '0');
        return true;
    }
    
    return false;
}


char Palette::getCurrentData () 
{
    return currentData;
}