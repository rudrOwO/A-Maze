#pragma once
#include <SFML/Graphics.hpp>
#include "tile_matrix.h"
#include <vector>
#include <map>
#include <utility>


class palette
{
private:
    float unit;
    static char currentData;
    const char drawSequence[9] = {'*', '0', '1', '2', '3', '4', '5', '6', '7'};
    sf::Font firaCode;
    sf::Vector2f origin;
    std::vector<std::pair<sf::RectangleShape, sf::Text>> shapeWithText;

public:
    static const std::map<char, std::pair<sf::Color, sf::Color>> colors;
    
    palette ();

    void draw ();
    bool onPaletteClick ();

    static char getCurrentData ();
};