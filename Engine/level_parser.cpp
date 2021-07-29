#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../Assets/tile.h"
// use noskipws manipulator

// maybe use a enum class to sort out globalUnit ?

// * for no-data tile
// - for blank tile
// [0 ~ 9] for data
// ! for finish tile


void loadLevel (int levelNumber, std::vector<std::vector<tile>>& tileMatrix)
{       
    std::fstream levelFile;
    std::string levelFileName("Levels/level_" + std::to_string(levelNumber) + ".txt"), rowBuffer;
    int rowCount = 0, colCount = 0;
    std::vector<std:: string> dataMatrix;

    levelFile.open(levelFileName, std::ios_base::in);
    
    // Extracting the tile data matrix from Level file
    while (std::getline(levelFile, rowBuffer)) {
        if (rowBuffer == "")
            break;

        dataMatrix.push_back(rowBuffer);
    }
    
    rowCount = dataMatrix.size();
    colCount = dataMatrix[0].size();
    
    levelFile.close();
}