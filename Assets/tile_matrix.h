#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "palette.h"
#include "tile.h"


class tile_matrix
{
private:
    std::vector<std::vector<tile*>> tileMatrix; 
    sf::Vector2f origin;
    int rowCount, colCount;

public:
    tile_matrix (const std::vector<std::string>& dataMatrix, const std::vector<std::string>& initializerMatrix);
    
    bool onTileClick ();
    void draw ();
};