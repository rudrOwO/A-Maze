#include <SFML/Graphics.hpp>


int main()
{
    // setting up the game window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Impossible until it is done");
    window.setFramerateLimit(60);

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
    }

    return 0;
}