#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../Assets/tile.h"
/*****************************************************
* DON'T FORGET TO CONVERT FROM DIGITAL CO-ORDINATES *
*        TO PURE MATHEMIATICAL CO-ORDINATES         *
*****************************************************
* DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS *
*******************************************************/
// 41 / 182 part of the screen is reserved for tile-Matrix
// 1 / 14 is reserved for palette on the left
// 10 / 65 is reserved for deck on the right 


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix);


bool onTileClick ()
{
    
}


bool onPaletteClick ()
{
    
}


int main()
{
    // Launching a window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Some Puzzle Game Thingy" /*, sf::Style::Fullscreen */);
    window.setFramerateLimit(60);
    
/**************************
* ALL ASSETS OF THE GAME *
**************************/

    std::vector<std::vector<tile*>> tileMatrix;
    char currentPaletteColor;     
    

    loadLevel(1, tileMatrix);

    
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            window.close();
            
            // Handling all mouse clicks
            if (event.type == sf::Event::MouseButtonPressed)
                ;
        }

        window.clear(sf::Color(0x232834ff));

        for (const auto& tileRow : tileMatrix) {
            for (const auto& t : tileRow)
            window.draw(t->getShape()); 
        }

        window.display();
    }

    return 0;
}