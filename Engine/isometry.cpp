#include <SFML/Graphics.hpp>
#include "../Assets/tile.h"

// Functions for IsoMetric Transformations
void isometricIncrementX(sf::Vector2f &vec, int step)
{
    vec.x += step * Tile::unit;
    vec.y += step * 0.5f * Tile::unit;
}

void isometricDecrementX(sf::Vector2f &vec, int step)
{
    vec.x -= step * Tile::unit;
    vec.y -= step * 0.5f * Tile::unit;
}

void isometricIncrementY(sf::Vector2f &vec, int step)
{
    vec.x -= step * Tile::unit;
    vec.y += step * 0.5f * Tile::unit;
}

void isometricDecrementY(sf::Vector2f &vec, int step)
{
    vec.x += step * Tile::unit;
    vec.y -= step * 0.5f * Tile::unit;
}