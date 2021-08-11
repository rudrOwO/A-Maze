#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "assets.h"


/***********************************************************
*   DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS    *
************************************************************
*                IMPLEMENT A TICK RATE                     *
************************************************************
* 152 / 195 PART OF THE SCREEN IS RESERVED FOR TILE-MATRIX *
*       1 / 15 IS RESERVED FOR PALETTE ON THE LEFT         *
*        10 / 65 IS RESERVED FOR DECK ON THE RIGHT         *
***********************************************************/


void loadLevel (int levelNumber, Asset_collection&);


sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Potato", sf::Style::Fullscreen);
Asset_collection assets;


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
         
        window.clear(sf::Color(0x232834ff));

        assets.simulator->draw();
        assets.colorGuide->draw();
        assets.tileMap->draw(); 
        
        window.display();
    }

    return 0;
}