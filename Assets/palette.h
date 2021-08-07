#pragma once
#include "tile.h" 
#include <vector>
#include <map>
#include <utility>


class palette
{
private:
    float unit;
    sf::RenderWindow& window;
    const char& currentPaletteData;
    sf::Font firaCode;
    sf::Vector2f paletteBegin;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> shapeWithText;

public:
    static const std::map<char, std::pair<sf::Color, sf::Color>> colors;
    
    palette (sf::RenderWindow& window, const char& currentPaletteData);
    void draw ();
};