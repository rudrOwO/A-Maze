#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../Assets/tile.h"


/***************************************************
 * MAYBE USE AN ENUM CLASS TO SORT OUT GLOBALUNIT ? *
 *   MAYBE SET CUSTOM DESTINATION FOR EACH BOT ?   *
 ***************************************************/


/**************************
 *   * FOR NO-DATA TILE   *
 *    - FOR BLANK TILE    *
 *    [0 ~ 9] FOR DATA    *
 * ! FOR DESTINATION TILE *
 **************************/


void loadLevel (int levelNumber, std::vector<std::vector<tile>>& tileMatrix)
{       
    std::fstream levelFile;   // File stream for parsing level file
    std::string levelFileName("Levels/level_" + std::to_string(levelNumber) + ".txt"), rowBuffer;
    levelFile.open(levelFileName, std::ios_base::in);

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
    

    // Extracting the writability matrix; and then initializing the tile matrix; since now we have everything we need
    while (std::getline(levelFile, rowBuffer)) {
        if (rowBuffer == "")
            break;


    }
    

    levelFile.close();
}