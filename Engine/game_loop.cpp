#include <SFML/Graphics.hpp>
#include <vector>
#include "../Assets/tile.h"

/*****************************************************
 * DON'T FORGET TO CONVERT FROM DIGITAL CO-ORDINATES *
 *        TO PURE MATHEMIATICAL CO-ORDINATES         *
 *****************************************************/

/*******************************************************
 * DON'T FORGET TO IMPLEMENT DESTRUCTORS OF ALL ASSETS *
 *******************************************************/


void loadLevel (int levelNumber, std::vector<std::vector<tile*>>& tileMatrix);
void createPalette ();


int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Perfect Blue");
    window.setFramerateLimit(60);

    
    
    /**************************
     * ALL ASSETS OF THE GAME *
     **************************/

   // std::vector<std::vector<tile*>> tileMatrix;
    
    initializable_tile test('*', sf::Vector2f(100.f, 100.f));
    
    //createPalette ();
    //loadLevel(0, tileMatrix);

    
     while (window.isOpen())
     {
         // check all the window's events that were triggered since the last iteration of the loop
         sf::Event event;
         while (window.pollEvent(event))
         {
             // "close requested" event: we close the window
             if (event.type == sf::Event::Closed)
                 window.close();
         }

         window.clear(sf::Color::Black);
         window.draw(test.getShape());
         window.display();
     }

    return 0;
}