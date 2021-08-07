#pragma once
#include "tile.h" 
#include <vector>
#include <map>
#include <utility>


class palette
{
private:
    sf::Font firaCode;
    sf::Vector2f columnBegin;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> shapeWithText;

public:
    static const std::map<char, std::pair<sf::Color, sf::Color>> colors;
    
    palette (sf::RenderWindow& window);
    void draw (char currentPaletteData, sf::RenderWindow& window);
};