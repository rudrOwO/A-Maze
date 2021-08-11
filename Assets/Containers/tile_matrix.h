#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../palette.h"
#include "../tile.h"


class Tile_matrix
{
private:
    std::vector<std::vector<Tile*>> grid; 
    sf::Vector2f origin;
    sf::Texture* lockTexture;
    int rowCount, colCount;

public:
    Tile_matrix (const std::vector<std::string>& dataMatrix, const std::vector<std::string>& initializerMatrix);
    
    bool onTileClick ();
    void draw ();
};