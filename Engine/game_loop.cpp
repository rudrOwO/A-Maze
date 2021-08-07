#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "../Assets/tile.h"
#include "../Assets/palette.h"


/***********************************************************
*   DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS    *
************************************************************
*        REPLACE COLORS WITH BETTER TEXTURES               *
************************************************************
*  REDUCE ALPHA OF NON_INITIALIZABLE_TILE TO MARK THEM     *
************************************************************
*      ENCAPSULATE TILE-MATRIX INTO TILE-MAP CLASS         *
************************************************************
*      ENCAPSULATE BOTH CLICKER METHODS INTO CLASSES       *
************************************************************
* 152 / 195 PART OF THE SCREEN IS RESERVED FOR TILE-MATRIX *
*       1 / 15 IS RESERVED FOR PALETTE ON THE LEFT         *
*        10 / 65 IS RESERVED FOR DECK ON THE RIGHT         *
***********************************************************/


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix, sf::RenderWindow& window);


/**************************
* ALL ASSETS OF THE GAME *
**************************/
sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Some Puzzle Game Thingy", sf::Style::Fullscreen);
std::vector<std::vector<tile*>> tileMatrix; 
char currentPaletteData('0');     
palette colorGuide(window, currentPaletteData);


void updateBackground ()
{
    window.clear(sf::Color(0x232834ff));
    // draw pallette
    colorGuide.draw();
}

    
bool onTileClick ()
{
    int rowCount = tileMatrix.size(), 
        colCount = tileMatrix[0].size();

    static const sf::Vector2f origin = tileMatrix[0][0]->getPosition();

    // Calculating x, y co-ordinates relative to the origin of tile-Map
    int x = sf::Mouse::getPosition().x - (int)origin.x,
        y = sf::Mouse::getPosition().y - (int)origin.y,

        // Isometric Transformation
        isometricX = ((x / 2 + y) / (int)tile::unit),
        isometricY = ((y - x / 2) / (int)tile::unit);
        
    // Bound Check to see which tile is clicked on; if any
    if (isometricX >= 0 and isometricX < colCount and isometricY >= 0 and isometricY < rowCount) {
        tileMatrix[isometricY][isometricX]->onMouseClick(currentPaletteData);
        return true;
    }
    
    return false;
}


bool onPaletteClick ()
{
    static const sf::Vector2f origin = colorGuide.getPaletteBegin();
    
    // Calculating x, y co-ordinates relative to the origin of palette / colorGuide
    int x = sf::Mouse::getPosition().x - (int)origin.x,
        y = sf::Mouse::getPosition().y - (int)origin.y;
    
    x /= colorGuide.getUnit();
    y /= colorGuide.getUnit();

    // Bound Check to see which color is clicked on; if any
    if (x < 1 and y >= 0 and y < colorGuide.getPaletteSize()) {
        currentPaletteData = (y == 0 ? '*' : y - 1 + '0');
        return true;
    }
    
    return false;
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
                    if (onTileClick())
                        break;
                    if (onPaletteClick())
                        break;
            }
        }

        updateBackground();

        // Continuously draw all dynamic assets
        for (const auto& tileRow : tileMatrix) {
            for (const auto& t : tileRow)
            window.draw(t->getShape()); 
        }

        window.display();
    }

    return 0;
}