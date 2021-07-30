#include <SFML/Graphics.hpp>
#include <vector>
#include "../Assets/tile.h"

/*****************************************************
 * DON'T FORGET TO CONVERT FROM DIGITAL CO-ORDINATES *
 *        TO PURE MATHEMIATICAL CO-ORDINATES         *
 *****************************************************/

void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix);
void createPalette ();


int main()
{
    // setting up the game window
    //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Perfect Blue");
    //window.setFramerateLimit(60);

    
    
    /**************************
     * ALL ASSETS OF THE GAME *
     **************************/
    std::vector<std::vector<tile*>> tileMatrix;
    
    
    
    createPalette ();
    loadLevel(0, tileMatrix);

    
    // while (window.isOpen())
    // {
    //     // check all the window's events that were triggered since the last iteration of the loop
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         // "close requested" event: we close the window
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear(sf::Color::Black);
    //     window.display();
    // }

    return 0;
}