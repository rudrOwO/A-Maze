#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "isometry.h"
#include "../Assets/tile.h"


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix, sf::RenderWindow& window)
{       
    std::fstream levelFile;   // File stream for parsing level file
    std::string levelFileName("Levels/level_" + std::to_string(levelNumber) + ".txt"), rowBuffer;
    levelFile.open(levelFileName, std::ios_base::in);


/**************************
* GENERATING TILE-MATRIX *
**************************/
    
    int rowCount = 0, colCount = 0;
    std::vector<std:: string> dataMatrix;  // Matrix for storing data written on tiles
    

    // Extracting the tile data matrix from Level file
    while (std::getline(levelFile, rowBuffer)) {
        if (rowBuffer == "")
            break;

        dataMatrix.push_back(rowBuffer);
    }
    
    rowCount = dataMatrix.size();
    colCount = dataMatrix[0].size();

    // Resizing the empty tileMatrix to fit all tiles
    for (int i = 0; i < rowCount; ++i) {
        tileMatrix.push_back(std::vector<tile*>());
        tileMatrix[i].resize(colCount);
    }
    
    // Calulating the isometric position of the first tile in the matrix (0, 0)
    float reservedWidth = window.getSize().x * (152.f / 195.f), 
          initialX = 0.5f * (reservedWidth - (rowCount + colCount) * tile::unit) + (1.f / 15.f) * window.getSize().x + rowCount * tile::unit,
          initialY = 0.5f * (window.getSize().y - 0.5f * (rowCount + colCount) * tile::unit) + 0.5f * tile::unit;

    sf::Vector2f currentPosition(initialX, initialY);

    // Extracting the initialization matrix; and then initializing the tile matrix
    for (int y = 0 ;; ++y) {
        std::getline(levelFile, rowBuffer);
        if (rowBuffer == "")
            break;

        for (int x = 0; x < colCount; ++x) {
            switch(rowBuffer[x]) {
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


/**************************
 * GENERATING THE PALETTE *
 **************************/

    levelFile.close();
}