#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "assets.h"


void loadLevel (int levelNumber, Asset_collection& assets)
{       

    // These don't need any parsing for initialization
    assets.colorGuide = new Palette();
    assets.simulator = new Simulator();

    // File stream for parsing level file
    std::ifstream levelFile;   
    std::string levelFileName("Levels/level_" + std::to_string(levelNumber) + ".txt"), rowBuffer;

    levelFile.open(levelFileName, std::ios_base::in);

/**************************
*  PARSING TILE-MATRIX    *
**************************/
    
    std::vector<std:: string> dataMatrix, initializerMatrix;  // Matrix for storing data written on tiles

    // Extracting the tile data matrix from Level file
    while (std::getline(levelFile, rowBuffer)) {
        if (rowBuffer == "")
            break;

        dataMatrix.push_back(rowBuffer);
    }
    
    // Extracting the initializer matrix from the file
    while (std::getline(levelFile, rowBuffer)) {
        if (rowBuffer == "")
            break;

        initializerMatrix.push_back(rowBuffer);
    }


/**************************
*  PARSING BOT-MATRIX    *
**************************/
    

    assets.tileMap = new Tile_matrix(dataMatrix, initializerMatrix);
    
    levelFile.close();
}