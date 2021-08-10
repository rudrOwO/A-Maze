#include "simulator.h"
extern sf::RenderWindow window;

int Simulator::status = Simulator::paused;


Simulator::Simulator ():
    bgColor(0xbdbdbdff),
    origin(sf::Vector2f(((float)window.getSize().x - Simulator::unit * 4.f) / 2.f, 5.f))

{
    sf::Vector2f currentButtonPosition(origin);
    
    for (int i = 0; i < 4; ++i) {
        const auto& textureName = textureFileSequence[i];

        texturePointerSequence.push_back(new sf::Texture);
        texturePointerSequence.back()->loadFromFile("Textures/" + textureName + ".png");
        texturePointerSequence.back()->setSmooth(true);

        buttons.emplace_back(sf::Vector2f(Simulator::unit, Simulator::unit));
        buttons.back().setPosition(currentButtonPosition);

        sprites.emplace_back(buttons.back());
        sprites.back().setTexture(texturePointerSequence.back()); 

        // Dirty Fix; I will remove it once I edit the faulty textures
        if (i % 2 == 0) {
            sprites.back().setSize(sf::Vector2f(unit - 5.f, unit - 5.f));
            sprites.back().setPosition(currentButtonPosition + sf::Vector2f(3.f, 3.f));
        }
        
        buttons.back().setOutlineThickness(-2.f); 
        currentButtonPosition += sf::Vector2f(Simulator::unit, 0.f);
    }
}


int Simulator::getStatus ()
{
    return Simulator::status;    
}


bool Simulator::onMouseClick ()
{
    return false;
}


void Simulator::draw ()
{
    sf::Color grey(0xbdbdbdff), blue(0x2196f3ff), dark_blue(0x0069c0ff), dark_grey(0x8d8d8dff);

    for (int i = 0; i < buttons.size(); ++i) {
        buttons[i].setFillColor(currentIndex == i ? blue : grey);
        buttons[i].setOutlineColor(currentIndex == i ? dark_blue : dark_grey);

        window.draw(buttons[i]);
        window.draw(sprites[i]);
    }
}