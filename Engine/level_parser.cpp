#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "../Assets/tile_matrix.h"
#include "../Assets/palette.h"


extern tile_matrix* tileMap;
extern palette* colorGuide;
// bots
// cards


void loadLevel (int levelNumber)
{       
    // File stream for parsing level file
    std::fstream levelFile;   
    std::string levelFileName("Levels/level_" + std::to_string(levelNumber) + ".txt"), rowBuffer;

    levelFile.open(levelFileName, std::ios_base::in);

/**************************
* PARSING TILE-MATRIX *
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


    colorGuide = new palette();
    tileMap = new tile_matrix(dataMatrix, initializerMatrix);
    
    levelFile.close();
}