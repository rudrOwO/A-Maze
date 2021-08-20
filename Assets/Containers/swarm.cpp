#include "swarm.h"
extern sf::Window window;


Swarm::Swarm (std::ifstream& levelFile, Tile_matrix& tileMap):
    botTextures(4, std::vector<sf::Texture*>(4)),
    tileMap(tileMap)

{
    // Loading all the bot textures for the swarm
    std::string fileName("Textures/robot00.png");

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            botTextures[i][j] = new sf::Texture();

            fileName[14] = i + '0'; 
            fileName[15] = j + '0'; 

            botTextures[i][j]->loadFromFile(fileName);
        }
    }

    
    // construct bots from botMatrix
    int currentTextureSet = 0, direction;
    char state;
    sf::Vector2i logicalPostion;

    while (true) {
        // 1 1 a 0
        levelFile >> logicalPostion.x; 

        if (logicalPostion.x == 0)
            break; 
        
        levelFile >> logicalPostion.y >> state >> direction;
        bots.emplace_back(logicalPostion, state, direction, botTextures[currentTextureSet], tileMap);
        currentTextureSet = (currentTextureSet + 1) % 4;
    }
}


void Swarm::draw ()
{
    for (Bot& bot : bots)
        bot.draw();
}


Bot& Swarm::operator[] (int index)
{
    return bots[index];
}