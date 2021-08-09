#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../Assets/tile.h"
#include "../Assets/tile_matrix.h"
#include "../Assets/palette.h"


/***********************************************************
*   DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS    *
************************************************************
* 152 / 195 PART OF THE SCREEN IS RESERVED FOR TILE-MATRIX *
*       1 / 15 IS RESERVED FOR PALETTE ON THE LEFT         *
*        10 / 65 IS RESERVED FOR DECK ON THE RIGHT         *
***********************************************************/


void loadLevel (int levelNumber);


sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Some Puzzle Game Thingy", sf::Style::Fullscreen);

tile_matrix* tileMap;
palette* colorGuide;
// bots
// cards


int main()
{
    window.setFramerateLimit(60);

    loadLevel(1);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // Using 'Close Button' to close window
                case sf::Event::Closed:
                    window.close();
                    break;

                // Using 'Escape' to close window
                case sf::Event::KeyPressed:
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                        window.close(); 
                        break;
                    }
                      
                // Handling all mouse clicks
                case sf::Event::MouseButtonPressed:
                    if (tileMap->onTileClick())
                        break;
                    if (colorGuide->onPaletteClick())
                        break;
            }
        }

        window.clear(sf::Color(0x232834ff));

        colorGuide->draw();
        tileMap->draw(); 

        window.display();
    }

    return 0;
}