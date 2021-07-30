#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "../Assets/tile.h"


// Functions for IsoMetric Calculations
void isometricIncrementX (sf::Vector2f& vec, int step)
{
    vec.x += step * tile::unit;
    vec.y += step * 0.5f * tile::unit;
}

void isometricDecrementX (sf::Vector2f& vec, int step)
{
    vec.x -= step * tile::unit;
    vec.y -= step * 0.5f * tile::unit;
}

void isometricIncrementY (sf::Vector2f& vec, int step)
{
    vec.x -= step * tile::unit;
    vec.y += step * 0.5f * tile::unit;
}

void isometricDecrementY (sf::Vector2f& vec, int step)
{
    vec.x += step * tile::unit;
    vec.y -= step * 0.5f * tile::unit;
}


// Mapped tile data to a specific pair of colors
std::map<char, std::pair<sf::Color, sf::Color>> palette = {
    {'*', std::make_pair(sf::Color(0xbdbdbdff), sf::Color(0x8d8d8dff))},
    {'0', std::make_pair(sf::Color(0xec407aff), sf::Color(0xb4004eff))},
    {'1', std::make_pair(sf::Color(0x9c27b0ff), sf::Color(0x6a0080ff))},
    {'2', std::make_pair(sf::Color(0x00bcd4ff), sf::Color(0x008ba3ff))},
    {'3', std::make_pair(sf::Color(0x009688ff), sf::Color(0x00675bff))},
    {'4', std::make_pair(sf::Color(0x4caf50ff), sf::Color(0x087f23ff))},
    {'5', std::make_pair(sf::Color(0xffee58ff), sf::Color(0xc9bc1fff))},
    {'6', std::make_pair(sf::Color(0x607d8bff), sf::Color(0x34515eff))},
    {'7', std::make_pair(sf::Color(0x8d6e63ff), sf::Color(0x5f4339ff))},
    {'8', std::make_pair(sf::Color(0xc62828ff), sf::Color(0x8e0000ff))},
    {'9', std::make_pair(sf::Color(0xe4e65eff), sf::Color(0x7c8500ff))},
    {'!', std::make_pair(sf::Color(0x2196f3ff), sf::Color(0x0069c0ff))}   // Perfect Blue
};


void createPalette ()
{
    // Create Palette here    
}


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix)
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

    // Resizing the empty tileMatrix to fit all tiles
    for (int i = 0; i < rowCount; ++i) {
        tileMatrix.push_back(std::vector<tile*>());
        tileMatrix[i].resize(colCount);
    }
    
    
    // Extracting the writability matrix; and then initializing the tile matrix; since now we have everything we need
    int y = 0;
    sf::Vector2f currentPosition(colCount * tile::unit, 0.5f * tile::unit);

    while (std::getline(levelFile, rowBuffer)) {
        if (rowBuffer == "")
            break;

        for (int x = 0; x < colCount;) {
            if (rowBuffer[x] == '-')
                tileMatrix[y][x] = new void_tile();
            else if (rowBuffer[x] == '0')
                tileMatrix[y][x] = new non_initializable_tile(dataMatrix[y][x], currentPosition);
            else
                tileMatrix[y][x] = new initializable_tile(dataMatrix[y][x], currentPosition);

            ++x;
            isometricIncrementX(currentPosition, 1);
        }
        isometricDecrementX(currentPosition, colCount);
        isometricIncrementY(currentPosition, 1); 
        ++y;
    }

    levelFile.close();
}