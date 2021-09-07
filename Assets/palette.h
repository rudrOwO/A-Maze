#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <utility>

class Palette
{
private:
    float unit;
    static char currentData;
    const char drawSequence[9] = {'*', '0', '1', '2', '3', '4', '5', '6', '7'};
    sf::Color whiteBorder;
    sf::Vector2f origin;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> shapeWithText;

public:
    static const std::map<char, std::pair<sf::Color, sf::Color>> colors;

    Palette();

    void draw();
    bool onPaletteClick();

    static char getCurrentData();
};