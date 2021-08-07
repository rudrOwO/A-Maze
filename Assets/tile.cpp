#include "tile.h"
#include "palette.h"
#include <map>


tile::tile (char newData, const sf::Vector2f& newPosition):
    shape(sf::ConvexShape(4)),
    data(newData),
    position(newPosition - sf::Vector2f(0.f, 0.5f * unit))

{
    shape.setOutlineThickness(-3.f);

    // constructing 2:1 Aspect Ratio Tile for Isometric Projection
    shape.setPoint(0, newPosition + sf::Vector2f(-unit, 0.f));
    shape.setPoint(1, newPosition + sf::Vector2f(0.f, unit / 2.f));
    shape.setPoint(2, newPosition + sf::Vector2f(unit, 0.f));
    shape.setPoint(3, newPosition + sf::Vector2f(0.f, -unit / 2.f));
}


initializable_tile::initializable_tile (char newData, const sf::Vector2f& newPosition):
    tile(newData, newPosition)
{
    this->setShape(newData);
}


non_initializable_tile::non_initializable_tile (char newData, const sf::Vector2f& newPosition):
    tile(newData, newPosition)
{
    this->setShape(newData);
}


void_tile::void_tile (char newData, const sf::Vector2f& newPosition):
    tile(newData, newPosition)
{
    this->setShape(newData);
}


char tile::getData () const
{
    return data;
}


sf::Vector2f tile::getPosition () const
{
    return position;    
}


const sf::ConvexShape& tile::getShape () const
{
    return shape;
}


void initializable_tile::onMouseClick (char newData) 
{
    data = newData;
    setShape(newData);
}


void non_initializable_tile::onMouseClick (char newData)
{}


void void_tile::onMouseClick (char newData)
{}


void tile::setData (char newData)
{
    data = newData;
}


void initializable_tile::setShape (char newData)
{
    const auto& shapeColor = palette::colors.at(newData);

    shape.setFillColor(shapeColor.first);
    shape.setOutlineColor(shapeColor.second);
}


void non_initializable_tile::setShape (char newData)
{
    shape.setFillColor(palette::colors.at(newData).first);
    shape.setOutlineColor(sf::Color(0x0069c0ff));
}


void void_tile::setShape (char newData)
{
    shape.setFillColor(sf::Color(0x00000000));
    shape.setOutlineColor(sf::Color(0x00000000));
}


bool tile::isVoid ()
{
    return data == '-';
}


bool tile::isDestination ()
{
    return data == '!';
}