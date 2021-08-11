
#include <SFML/Graphics/RenderWindow.hpp>
#include "tile_matrix.h"
#include "../../Engine/isometry.h"
extern sf::RenderWindow window;


Tile_matrix::Tile_matrix (const std::vector<std::string>& dataMatrix, const std::vector<std::string>& initializerMatrix):
    rowCount(dataMatrix.size()),
    colCount(dataMatrix[0].size()),
    grid(dataMatrix.size(), std::vector<Tile*>(dataMatrix[0].size()))

{
    // Calulating the isometric position of the first tile in the matrix (0, 0)
    float reservedWidth = window.getSize().x * (152.f / 195.f), 
          initialX = 0.5f * (reservedWidth - (rowCount + colCount) * Tile::unit) + (1.f / 15.f) * window.getSize().x + rowCount * Tile::unit,
          initialY = 0.5f * (window.getSize().y - 0.5f * (rowCount + colCount) * Tile::unit) + 0.5f * Tile::unit;

    sf::Vector2f currentPosition(initialX, initialY);

    // Extracting the initializer matrix; and then populating the tile matrix
    for (int y = 0 ; y < rowCount; ++y) {
        for (int x = 0; x < colCount; ++x) {
            switch(initializerMatrix[y][x]) {
                case '-':
                    grid[y][x] = new Void_tile(dataMatrix[y][x], currentPosition);
                    break;
                case '0':
                    grid[y][x] = new Non_initializable_tile(dataMatrix[y][x], currentPosition);
                    break;
                default:
                    grid[y][x] = new Initializable_tile(dataMatrix[y][x], currentPosition);
            } 

            isometricIncrementX(currentPosition);
        }

        isometricDecrementX(currentPosition, colCount);
        isometricIncrementY(currentPosition); 
    }

    origin = grid[0][0]->getPosition();
}


bool Tile_matrix::onTileClick ()
{
    // Calculating x, y co-ordinates relative to the origin of tile-Map
    int x = sf::Mouse::getPosition().x - (int)origin.x,
        y = sf::Mouse::getPosition().y - (int)origin.y,

        // Isometric Transformation
        isometricX = ((x / 2 + y) / (int)Tile::unit),
        isometricY = ((y - x / 2) / (int)Tile::unit);
        
    // Bound Check to see which tile is clicked on; if any
    if (isometricX >= 0 and isometricX < colCount and isometricY >= 0 and isometricY < rowCount) {
        grid[isometricY][isometricX]->onMouseClick(Palette::getCurrentData());
        return true;
    }
    
    return false;
}


void Tile_matrix::draw ()
{
    for (int y = 0; y < rowCount; ++y) {
        for (int x = 0; x < colCount; ++x)
            grid[y][x]->draw();
    }
}