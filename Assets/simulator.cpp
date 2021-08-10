#include "simulator.h"
extern sf::RenderWindow window;

// grey 0xbdbdbdff
// blue 0x2196f3ff

Simulator::Simulator ():
    bgColor(0xbdbdbdff),
    origin(sf::Vector2f(((float)window.getPosition().x - Simulator::unit * buttonCount) / 2.f, 5.f)),
    buttons(buttonCount, sf::RectangleShape(sf::Vector2f(Simulator::unit, Simulator::unit)))

{
    sf::Texture filler;

    for (const auto& texture : textureFileSequence) {
        
    }
}


static int getStatus ()
{
    return 0;    
}


bool Simulator::onMouseClick ()
{
    return false;
}


void Simulator::draw ()
{
    
}