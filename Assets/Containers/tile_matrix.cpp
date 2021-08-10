
#include <SFML/Graphics/RenderWindow.hpp>
#include "tile_matrix.h"
#include "../../Engine/isometry.h"
extern sf::RenderWindow window;


tile_matrix::tile_matrix (const std::vector<std::string>& dataMatrix, const std::vector<std::string>& initializerMatrix):
    rowCount(dataMatrix.size()),
    colCount(dataMatrix[0].size()),
    tileMatrix(dataMatrix.size(), std::vector<tile*>(dataMatrix[0].size()))

{
    // Calulating the isometric position of the first tile in the matrix (0, 0)
    float reservedWidth = window.getSize().x * (152.f / 195.f), 
          initialX = 0.5f * (reservedWidth - (rowCount + colCount) * tile::unit) + (1.f / 15.f) * window.getSize().x + rowCount * tile::unit,
          initialY = 0.5f * (window.getSize().y - 0.5f * (rowCount + colCount) * tile::unit) + 0.5f * tile::unit;

    sf::Vector2f currentPosition(initialX, initialY);

    // Extracting the initializer matrix; and then populating the tile matrix
    for (int y = 0 ; y < rowCount; ++y) {
        for (int x = 0; x < colCount; ++x) {
            switch(initializerMatrix[y][x]) {
                case '-':
                    tileMatrix[y][x] = new void_tile(dataMatrix[y][x], currentPosition);
                    break;
                case '0':
                    tileMatrix[y][x] = new non_initializable_tile(dataMatrix[y][x], currentPosition);
                    break;
                default:
                    tileMatrix[y][x] = new initializable_tile(dataMatrix[y][x], currentPosition);
            } 

            isometricIncrementX(currentPosition);
        }

        isometricDecrementX(currentPosition, colCount);
        isometricIncrementY(currentPosition); 
    }

    origin = tileMatrix[0][0]->getPosition();
}


bool tile_matrix::onTileClick ()
{
    // Calculating x, y co-ordinates relative to the origin of tile-Map
    int x = sf::Mouse::getPosition().x - (int)origin.x,
        y = sf::Mouse::getPosition().y - (int)origin.y,

        // Isometric Transformation
        isometricX = ((x / 2 + y) / (int)tile::unit),
        isometricY = ((y - x / 2) / (int)tile::unit);
        
    // Bound Check to see which tile is clicked on; if any
    if (isometricX >= 0 and isometricX < colCount and isometricY >= 0 and isometricY < rowCount) {
        tileMatrix[isometricY][isometricX]->onMouseClick(palette::getCurrentData());
        return true;
    }
    
    return false;
}


void tile_matrix::draw ()
{
    for (int y = 0; y < rowCount; ++y) {
        for (int x = 0; x < colCount; ++x)
            // getShape() is awaiting upgrade
            window.draw(tileMatrix[y][x]->getShape());
    }
}