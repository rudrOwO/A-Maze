#include <SFML/Graphics.hpp>
#include "../Assets/tile.h"


// Functions for IsoMetric Calculations
void isometricIncrementX (sf::Vector2f& vec, int step = 1)
{
    vec.x += step * tile::unit;
    vec.y += step * 0.5f * tile::unit;
}

void isometricDecrementX (sf::Vector2f& vec, int step = 1)
{
    vec.x -= step * tile::unit;
    vec.y -= step * 0.5f * tile::unit;
}

void isometricIncrementY (sf::Vector2f& vec, int step = 1)
{
    vec.x -= step * tile::unit;
    vec.y += step * 0.5f * tile::unit;
}

void isometricDecrementY (sf::Vector2f& vec, int step = 1)
{
    vec.x += step * tile::unit;
    vec.y -= step * 0.5f * tile::unit;
}