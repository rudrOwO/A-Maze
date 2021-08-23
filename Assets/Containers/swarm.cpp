#include "swarm.h"
extern sf::RenderWindow window;


Swarm::Swarm ():
    collisionCheck(std::vector<std::vector<int>>(60, std::vector<int>(60, 0))),
    botTextures(4, std::vector<sf::Texture*>(4))

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

}


void Swarm::draw ()
{
    for (auto& bot : bots)
        bot->draw();
}


void Swarm::pollActions ()
{
    for (auto& bot : bots) {
        bot->pollActionQueue();

        // Updating Collision check; since there is possibitllity of a change in position upon polling the bots for actions
        const auto& logicalPos = bot->getLogicalPosition(); 
        ++collisionCheck[logicalPos.y][logicalPos.x];
    }
}


void Swarm::checkStatus ()
{
    // Check Out-of-Bounds; Mutual Collision; and Destination Status; 
    for (int i = 0; i < bots.size(); ++i) {
        Bot* &bot = bots[i];
        
        if (bot->isBotDEAD()) {
            Simulator::setStatus(Simulator::gameOver);
            return;
        }

        const sf::Vector2i& logicalPos = bot->getLogicalPosition(); 

        if (collisionCheck[logicalPos.y][logicalPos.x] > 1) {
            Simulator::setStatus(Simulator::gameOver);
            return;
        } else {
            collisionCheck[logicalPos.y][logicalPos.x] = 0;
        }
        
        if (bot->isBotDONE()) {
            delete bot;
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