#include "simulator.h"
extern sf::RenderWindow window;

int Simulator::status = Simulator::paused;

Simulator::Simulator() : grey(0xbdbdbdff), blue(0x2196f3ff), dark_blue(0x0069c0ff), dark_grey(0x8d8d8dff),
                         origin(sf::Vector2f(((float)window.getSize().x - Simulator::unit * 4.f) / 2.f, 5.f))

{
    sf::Vector2f currentButtonPosition(origin);

    for (int i = 0; i < 4; ++i)
    {
        const auto &textureName = textureFileSequence[i];

        texturePointerSequence.push_back(new sf::Texture);
        texturePointerSequence.back()->loadFromFile("Textures/" + textureName + ".png");
        texturePointerSequence.back()->setSmooth(true);

        buttons.emplace_back(sf::Vector2f(Simulator::unit, Simulator::unit));
        buttons.back().setPosition(currentButtonPosition);

        sprites.emplace_back(buttons.back());
        sprites.back().setTexture(texturePointerSequence.back());
        sprites.back().setScale(0.8f, 0.8f);
        sprites.back().move(5.f, 5.f);

        buttons.back().setOutlineThickness(-2.f);
        currentButtonPosition += sf::Vector2f(Simulator::unit, 0.f);
    }
}

int Simulator::getStatus()
{
    return Simulator::status;
}

bool Simulator::onMouseClick()
{
    // Calculating x, y co-ordinates relative to the origin of simulator
    int x = sf::Mouse::getPosition().x - (int)origin.x,
        y = sf::Mouse::getPosition().y - (int)origin.y;

    x /= Simulator::unit;
    y /= Simulator::unit;

    // Bound Check to see which button is clicked on; if any
    if (y < 1 and x >= 0 and x < 4)
    {
        Simulator::setStatus(x);
        return true;
    }

    return false;
}

void Simulator::setStatus(int newStatus)
{
    Simulator::status = newStatus;
}

void Simulator::draw()
{
    for (int i = 0; i < buttons.size(); ++i)
    {
        buttons[i].setFillColor(Simulator::status == i ? blue : grey);
        buttons[i].setOutlineColor(Simulator::status == i ? dark_blue : dark_grey);

        window.draw(buttons[i]);
        window.draw(sprites[i]);
    }
}