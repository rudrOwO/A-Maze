#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../Assets/tile.h"
#include "../Assets/palette.h"

/***************************************************
* DON'T FORGET TO CONVERT FROM SCREEN CO-ORDINATES *
*        TO MATHEMIATICAL CO-ORDINATES             *
*******************************************************
* DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS *
***********************************************************
* REFACTOR TILE CLASS TO INITIALIZE MEMBERS IN BASE CLASS *
*        REPLACE COLORS WITH BETTER TEXTURES              *
***********************************************************
 * 141 / 182 PART OF THE SCREEN IS RESERVED FOR TILE-MATRIX *
 *       1 / 14 IS RESERVED FOR PALETTE ON THE LEFT        *
 *        10 / 65 IS RESERVED FOR DECK ON THE RIGHT        *
 ***********************************************************/


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix, sf::RenderWindow& window);


/**************************
* ALL ASSETS OF THE GAME *
**************************/
sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Some Puzzle Game Thingy"/*, sf::Style::Fullscreen*/);
std::vector<std::vector<tile*>> tileMatrix;
char currentPaletteData('0');     
    
    
bool onTileClick ()
{
    // Calculating x, y co-ordinates relative to the origin of tile-Map
    const sf::Vector2f& origin = tileMatrix[0][0]->getPosition();

    int rowCount = tileMatrix.size(),
        colCount = tileMatrix[0].size(),
        x = sf::Mouse::getPosition(window).x - (int)origin.x,
        y = sf::Mouse::getPosition(window).y - (int)origin.y,
        isometricX = ((2 * y + x) / (int)tile::unit) - rowCount,
        isometricY = ((2 * y - x) / (int)tile::unit) - rowCount;
        
    if (isometricX >= 0 and isometricX < colCount and isometricY >= 0 and isometricY < rowCount) {
        tileMatrix[isometricY][isometricX]->onMouseClick(currentPaletteData);
        return true;
    }
    
    return false;
}


bool onPaletteClick ()
{
    
}


int main()
{
    window.setFramerateLimit(60);

    loadLevel(1, tileMatrix, window);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                // "close requested" event: we close the window
                case sf::Event::Closed:
                    window.close();
                    break;
                
                // Handling all mouse clicks
                case sf::Event::MouseButtonPressed:
                    if (onTileClick())
                        ;
                    else if (onPaletteClick())
                        ;
            }
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