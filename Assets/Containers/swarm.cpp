#include "swarm.h"
extern sf::Window window;


Swarm::Swarm (std::ifstream& levelFile, Tile_matrix& tileMap):
    collisionCheck(std::vector<std::vector<int>>(100, std::vector<int>(100, 0))),
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
        bots.push_back(Bot(logicalPostion, (int)state, direction, botTextures[currentTextureSet], tileMap));
        currentTextureSet = (currentTextureSet + 1) % 4;
    }
}


void Swarm::draw ()
{
    for (Bot& bot : bots)
        bot.draw();
}


void Swarm::pollActions ()
{
    for (Bot& bot : bots) {
        bot.pollActionQueue();

        const auto& logicalPos = bot.getLogicalPosition(); 
        ++collisionCheck[logicalPos.y][logicalPos.x];
    }
}


void Swarm::checkStatus ()
{
    // Check Out-of-Bounds; Mutual Collision; and destination status; 
    for (int i = 0; i < bots.size(); ++i) {
        //Bot& bot = bots[i];
        
        if (bots[i].isBotDEAD()) {
            Simulator::setStatus(Simulator::gameOver);
            return;
        }

        const auto& logicalPos = bots[i].getLogicalPosition(); 

        if (collisionCheck[logicalPos.y][logicalPos.x] > 1) {
            Simulator::setStatus(Simulator::gameOver);
            return;
        } else {
            collisionCheck[logicalPos.y][logicalPos.x] = 0;
        }
        
        if (bots[i].isBotDONE()) {
            // implement destruction
            bots.erase(bots.begin() + i);

            if (bots.empty()) {
                Simulator::setStatus(Simulator::levelPassed);
                return;
            }  
             
            if (++i >= bots.size()) 
                i = -1;
        }
    }
}


//Bot& Swarm::operator[] (int index)
//{
//    return bots[index];
//}