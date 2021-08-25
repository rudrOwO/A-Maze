#include <SFML/Graphics.hpp>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include "assets.h"
extern Asset_collection assets;
extern sf::Font firaCode;


void loadLevel (int levelNumber)
{       
    // Loading a global font that is used for all sorts of text display
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
        if (rowBuffer == "<<")
            break;

        dataMatrix.push_back(rowBuffer);
    }
    
    // Extracting the initializer matrix from the file
    while (levelFile >> rowBuffer) {
        if (rowBuffer == "<<")
            break;

        initializerMatrix.push_back(rowBuffer);
    }

    assets.tileMap = new Tile_matrix(dataMatrix, initializerMatrix);

/*************************
*  PARSING BOT-MATRIX    *
*************************/
    assets.swarm = new Swarm();
    
    int currentTextureSet = 0, direction;
    char state;
    sf::Vector2i logicalPostion;

    while (levelFile >> logicalPostion.x) {
        if (logicalPostion.x == 0)
            break; 
        
        levelFile >> logicalPostion.y >> state >> direction;

        assets.swarm->bots.push_back(new Bot(
            logicalPostion, state, direction, 
            assets.swarm->botTextures[currentTextureSet], 
            assets.tileMap, assets.deck
        ));

        currentTextureSet = (currentTextureSet + 1) % 4;
    }
    
/*************************
*    PARSING THE DECK    *
*************************/
    assets.deck = new Deck();
     
    std::pair<std::string, std::string> token;
    bool isScopped = false;
    Card* currentCard;
        
    while (levelFile >> token.first) {
        if (token.first.size() == 1) {
            assets.deck->cards.insert({
                token.first[0], currentCard = new Card()
            });

            assets.deck->displayMessage.insert(25, token.first + ","); 

        } else if (token.first == "<<") {
            currentCard->push_line(isScopped, {"", ""});
        
        } else if (token.first == ">>") {
            isScopped = true;
            continue;
             
        } else {
            levelFile >> token.second;
            currentCard->push_line(isScopped, token);
        } 
        
        isScopped = false;
    };

    assets.deck->nowEditing = assets.deck->cards.begin();
    
    // Parsing ends; All assets instantiated and populated with appropariate contents    
    levelFile.close();
}