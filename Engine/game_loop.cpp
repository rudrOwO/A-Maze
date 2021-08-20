#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "assets.h"


/************************************************************
*   DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS     *
*************************************************************
* REFACTOR LEVEL PARSER FOR BETTER EXTRACTION WITH IFSTREAM *
*************************************************************
*          IMPLEMENT COLLISION DETECTION FOR BOTS           * 
*************************************************************
* 152 / 195 PART OF THE SCREEN IS RESERVED FOR TILE-MATRIX  *
*       1 / 15 IS RESERVED FOR PALETTE ON THE LEFT          *
*        10 / 65 IS RESERVED FOR DECK ON THE RIGHT          *
************************************************************/


void loadLevel (int levelNumber, Asset_collection&);


// These are all the resources you need for the game
sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Potato", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Potato"/*, sf::Style::Fullscreen */);
Asset_collection assets;
sf::Color backgroundColor(0x232834ff);
std::chrono::duration<unsigned int, std::milli> tickRate(450);


int main()
{
    window.setFramerateLimit(60);

    loadLevel(0, assets);


    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // Using 'Escape' to close window
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window.close(); 
                        break;
                    }
                      
                // Handling all mouse clicks
                case sf::Event::MouseButtonPressed:
                    if (assets.simulator->onMouseClick())
                        break;
                    if (assets.tileMap->onTileClick())
                        break;
                    if (assets.colorGuide->onPaletteClick())
                        break;
            }
        }

        window.clear(backgroundColor); 
        
        assets.swarm->pollActions();
        assets.swarm->checkStatus();

        assets.simulator->draw();
        assets.colorGuide->draw();
        assets.tileMap->draw(); 
        assets.swarm->draw();

        std::this_thread::sleep_for(tickRate);
     
        window.display();
    }

    return 0;
}