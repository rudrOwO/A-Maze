#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "assets.h"
extern Asset_collection assets;
extern sf::Font firaCode;


void loadLevel (int levelNumber)
{       
    firaCode.loadFromFile("Fonts/FiraCode-Regular.woff");

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
    while (levelFile >> rowBuffer) {
        if (rowBuffer == ">>")
            break;

        dataMatrix.push_back(rowBuffer);
    }
    
    // Extracting the initializer matrix from the file
    while (levelFile >> rowBuffer) {
        if (rowBuffer == ">>")
            break;

        initializerMatrix.push_back(rowBuffer);
    }

    assets.tileMap = new Tile_matrix(dataMatrix, initializerMatrix);

/*************************
*  PARSING BOT-MATRIX    *
**************************/
    
    assets.swarm = new Swarm(*assets.tileMap);
    
    int currentTextureSet = 0, direction;
    char state;
    sf::Vector2i logicalPostion;

    while (true) {
        levelFile >> logicalPostion.x; 

        if (logicalPostion.x == 0)
            break; 
        
        levelFile >> logicalPostion.y >> state >> direction;

        assets.swarm->bots.push_back(new Bot(
            logicalPostion, state, direction, 
            assets.swarm->botTextures[currentTextureSet], 
            assets.swarm->tileMap
        ));

        currentTextureSet = (currentTextureSet + 1) % 4;
    }
    
    
/*************************
*    PARSING THE DECK    *
**************************/

    levelFile.close();
}