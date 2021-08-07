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


palette::palette (sf::RenderWindow& window, const char& currentPaletteData):
    window(window),
    currentPaletteData(currentPaletteData),
    unit(window.getSize().y / 14.f),
    paletteBegin(0.f, (window.getSize().y - 10.f * palette::unit) / 2.f)


{
    firaCode.loadFromFile("Fonts/FiraCode-Regular.woff"); 

    sf::Text fillerText;
    sf::RectangleShape fillerShape(sf::Vector2f(palette::unit, palette::unit));

    fillerText.setFont(firaCode);
    fillerText.setCharacterSize(25);
    fillerShape.setOutlineThickness(-4.f);
    
    for (char c = '0'; c <= '9'; ++c, paletteBegin += sf::Vector2f(0.f, palette::unit)) {
        fillerText.setString(c);

        const auto& color = palette::colors.at(c);
        fillerShape.setFillColor(color.first);
        fillerShape.setOutlineColor(c == currentPaletteData ? sf::Color(0xddddddff) : color.second);

        fillerText.setPosition(paletteBegin + sf::Vector2f(5.f, 5.f));
        fillerShape.setPosition(paletteBegin);
        
        shapeWithText.emplace_back(fillerShape, fillerText);
    }
}


void palette::draw ()
{
    for (const auto& it : shapeWithText) {
        window.draw(it.first);
        window.draw(it.second);
    }
}