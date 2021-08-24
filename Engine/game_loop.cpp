#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "assets.h"


/************************************************************
*  MAKE READING SEAMLESS WITH THE GAME TICK ? I.E. NO DELAY *
*************************************************************
*            IMPLEMENT DESTRUCTORS OF ALL ASSETS            *
*************************************************************
*              IMPLEMENT BOT STATE INDICATOR                *
*************************************************************
*           HANDLE INPUT IN A DIFFERENT THREAD ?            *
*************************************************************
*         OVERLOAD PALETTE CLASS AND CREATE A MENU          *
*************************************************************
* 1/15 PART OF Y AXIS IS RESERVED FOR PALETTE ON THE LEFT   *
*  1/5 OF X AXIS IS RESERVED FOR DECK ON THE RIGHT          *
************************************************************/


void loadLevel (int levelNumber);


// These are all the resources you need for the game
sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Botomata", sf::Style::Fullscreen);
//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Botomata"/*, sf::Style::Fullscreen */);
Asset_collection assets;
sf::Color backgroundColor(0x232834ff);
sf::Font firaCode;
std::chrono::duration<unsigned int, std::milli> tickRate(450);


int main()
{
    window.setFramerateLimit(60);
    loadLevel(0);


    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))  // Using 'Escape' to close window
                        window.close(); 

                    else if (Simulator::getStatus() == Simulator::paused)
                        assets.deck->onKeyPress(event); 

                    break;
                      
                // Handling all mouse clicks
                case sf::Event::MouseButtonPressed:
                    if (assets.simulator->onMouseClick())
                        break;

                    if (Simulator::getStatus() == Simulator::paused) {
                        if (assets.tileMap->onTileClick())
                            break;

                        if (assets.colorGuide->onPaletteClick())
                            break;
                    }
            }
        }

        window.clear(backgroundColor); 

        if (Simulator::getStatus() == Simulator::running) { 
            if (not assets.deck->isInterpreted())
                assets.deck->interpretAll();

            assets.swarm->pollActions();
            assets.swarm->checkStatus();

            std::this_thread::sleep_for(tickRate);
        }
        
        assets.colorGuide->draw();
        assets.simulator->draw();
        assets.tileMap->draw(); 
        assets.swarm->draw();
        assets.deck->draw();

        window.display();
    }

    return 0;
}