#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "isometry.h"
#include "../Assets/tile.h"


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix)
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
    
    
    // Extracting the writability matrix; and then initializing the tile matrix; since now we have everything we need
    sf::Vector2f currentPosition(colCount * tile::unit, 0.5f * tile::unit);

    for (int y = 0 ;; ++y) {
        std::getline(levelFile, rowBuffer);
        if (rowBuffer == "")
            break;

        for (int x = 0; x < colCount; ++x) {
            if (rowBuffer[x] == '-')
                tileMatrix[y][x] = new void_tile();
            else if (rowBuffer[x] == '0')
                tileMatrix[y][x] = new non_initializable_tile(dataMatrix[y][x], currentPosition);
            else
                tileMatrix[y][x] = new initializable_tile(dataMatrix[y][x], currentPosition);
            
            isometricIncrementX(currentPosition);
        }
        isometricDecrementX(currentPosition, colCount);
        isometricIncrementY(currentPosition); 
    }


    levelFile.close();
}