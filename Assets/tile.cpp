#include "tile.h"
#include "palette.h"
extern sf::RenderWindow window;


Tile::Tile (char newData, const sf::Vector2f& newPosition):
    shapes(3, sf::ConvexShape(4)),
    data(newData),
    position(newPosition - sf::Vector2f(0.f, 0.5f * unit))

{
    for (auto& shape : shapes) {
        shape.setOutlineThickness(-0.75f);
        shape.setOutlineColor(sf::Color::Black);
    }

    // constructing 2:1 Aspect Ratio Tile for Isometric Projection; in counter-clockwise turn
    shapes[0].setPoint(0, newPosition + sf::Vector2f(-unit, 0.f));
    shapes[0].setPoint(1, newPosition + sf::Vector2f(0.f, unit / 2.f));
    shapes[0].setPoint(2, newPosition + sf::Vector2f(unit, 0.f));
    shapes[0].setPoint(3, newPosition + sf::Vector2f(0.f, -unit / 2.f));
    
    // Constructing a composite shape for pseudo 3D effect 
    shapes[1].setPoint(0, newPosition + sf::Vector2f(-unit, 0.f));
    shapes[1].setPoint(1, newPosition + sf::Vector2f(0.f, unit / 2.f));
    shapes[1].setPoint(2, shapes[1].getPoint(1) + sf::Vector2f(0.f, height));
    shapes[1].setPoint(3, shapes[1].getPoint(0) + sf::Vector2f(0.f, height));
    
    shapes[2].setPoint(0, newPosition + sf::Vector2f(0.f, unit / 2.f));
    shapes[2].setPoint(1, newPosition + sf::Vector2f(unit, 0.f));
    shapes[2].setPoint(2, shapes[2].getPoint(1) + sf::Vector2f(0.f, height));
    shapes[2].setPoint(3, shapes[2].getPoint(0) + sf::Vector2f(0.f, height));
}


Initializable_tile::Initializable_tile (char newData, const sf::Vector2f& newPosition):
    Tile(newData, newPosition)

{
    this->setShape(newData);
}


Non_initializable_tile::Non_initializable_tile (char newData, const sf::Vector2f& newPosition):
    Tile(newData, newPosition),
    crossShape { 
        sf::RectangleShape(sf::Vector2f(2 * Tile::unit, 2.f)), 
        sf::RectangleShape(sf::Vector2f(2.f, Tile::unit)) 
    }

{
    this->setShape(newData);
    
    crossShape[0].setOrigin(Tile::unit, 1.f);
    crossShape[1].setOrigin(1.f, Tile::unit / 2.f);
    
    crossShape[0].setScale(0.33f, 1.f);
    crossShape[1].setScale(1.f, 0.33f);

    for (int i : {0, 1}) {
        crossShape[i].setPosition(this->getPosition() + sf::Vector2f(0.f, 0.5f * Tile::unit));
        crossShape[i].setFillColor(sf::Color::Black);
    } 
    
    if (isDestination())
        shapes[0].setOutlineThickness(-3.f);
}


Void_tile::Void_tile (char newData, const sf::Vector2f& newPosition):
    Tile(newData, newPosition)

{}


char Tile::getData () const
{
    return data;
}


sf::Vector2f Tile::getPosition () const
{
    return position;    
}


void Initializable_tile::onMouseClick (char newData) 
{
    data = newData;
    setShape(newData);
}


void Non_initializable_tile::onMouseClick (char newData)
{}


void Void_tile::onMouseClick (char newData)
{}


void Tile::setData (char newData)
{
    data = newData;
}


void Tile::setShape (char newData)
{
    const auto& shapeColor = Palette::colors.at(newData);

    shapes[0].setFillColor(shapeColor.first);
    shapes[1].setFillColor(shapeColor.second);
    shapes[2].setFillColor(shapeColor.second);
}


bool Tile::isVoid ()
{
    return data == '-';
}


bool Tile::isDestination ()
{
    return data == '!';
}


void Initializable_tile::draw ()
{
    for (auto& shape : shapes)
        window.draw(shape);
}


void Non_initializable_tile::draw ()
{
    for (auto& shape : shapes)
        window.draw(shape);
    
    if (Simulator::getStatus() == Simulator::paused) {
        window.draw(crossShape[0]);
        window.draw(crossShape[1]);
    }
}


void Void_tile::draw ()
{}