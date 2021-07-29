#include <SFML/Graphics.hpp>
#include <vector>
#include "../Assets/tile.h"

/*****************************************************
 * DON'T FORGET TO CONVERT FROM DIGITAL CO-ORDINATES *
 *        TO PURE MATHEMIATICAL CO-ORDINATES         *
 *****************************************************/

void loadLevel (int levelNumber, std::vector<std::vector<tile>>& tileMatrix);

int main()
{
    // setting up the game window
    //sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Impossible until it's done");
    //window.setFramerateLimit(60);

    

    std::vector<std::vector<tile>> tileMatrix;
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