#include "swarm.h"
extern sf::Window window;


Swarm::Swarm (const std::vector<std::string>& botMatrix, Tile_matrix& tileMap):
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
    int currentTextureSet = 0;
    for (const auto& parseRow : botMatrix) {
        // 1 1 A 0
        bots.emplace_back( sf::Vector2i(parseRow[0] - '0', parseRow[2] - '0'),   // logical Position
                           parseRow[4],  // state
                           parseRow[6] - '0',   // direction
                           botTextures[currentTextureSet],  // one suite of textures
                           tileMap  // reference to tileMap
                        );
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