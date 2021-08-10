#include "tile.h"
#include "palette.h"
extern sf::RenderWindow window;


Tile::Tile (char newData, const sf::Vector2f& newPosition):
    shapes(3, sf::ConvexShape(4)),
    data(newData),
    position(newPosition - sf::Vector2f(0.f, 0.5f * unit))

{
    for (auto& shape : shapes) {
        shape.setOutlineThickness(-1.f);
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
    shapes[1].setPoint(2, shapes[1].getPoint(0) + sf::Vector2f(0.f, 10.f));
    shapes[1].setPoint(3, shapes[1].getPoint(1) + sf::Vector2f(0.f, 10.f));
    
    
    shapes[2].setPoint(0, newPosition + sf::Vector2f(0.f, unit / 2.f));
    shapes[2].setPoint(1, newPosition + sf::Vector2f(unit, 0.f));
    shapes[2].setPoint(2, shapes[2].getPoint(0) + sf::Vector2f(0.f, 10.f));
    shapes[2].setPoint(3, shapes[2].getPoint(1) + sf::Vector2f(0.f, 10.f));
}


Initializable_tile::Initializable_tile (char newData, const sf::Vector2f& newPosition):
    Tile(newData, newPosition)
{
    this->setShape(newData);
}


Non_initializable_tile::Non_initializable_tile (char newData, const sf::Vector2f& newPosition):
    Tile(newData, newPosition)
{
    this->setShape(newData);
}


Void_tile::Void_tile (char newData, const sf::Vector2f& newPosition):
    Tile(newData, newPosition)
{
    this->setShape(newData);
}


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


void Initializable_tile::setShape (char newData)
{
    const auto& shapeColor = Palette::colors.at(newData);

    shape.setFillColor(shapeColor.first);
    shape.setOutlineColor(shapeColor.second);
}


void Non_initializable_tile::setShape (char newData)
{
    shape.setFillColor(Palette::colors.at(newData).first);
    shape.setOutlineColor(sf::Color(0x0069c0ff));
}


void Void_tile::setShape (char newData)
{
    shape.setFillColor(sf::Color(0x00000000));
    shape.setOutlineColor(sf::Color(0x00000000));
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
    
}


void Non_initializable_tile::draw ()
{
    
}


void Void_tile::draw ()
{
    
}