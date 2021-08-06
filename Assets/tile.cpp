#include "tile.h"
#include "palette.h"
#include <map>


initializable_tile::initializable_tile (char newData, const sf::Vector2f& newPosition)
{
    shape = sf::ConvexShape(4);
    shape.setOutlineThickness(-3.f);
    data = newData;
    position = newPosition;
    this->setShape(newData);

    // constructing 2:1 Aspect Ratio Tile for Isometric Projection
    shape.setPoint(0, position + sf::Vector2f(-unit, 0.f));
    shape.setPoint(1, position + sf::Vector2f(0.f, unit / 2.f));
    shape.setPoint(2, position + sf::Vector2f(unit, 0.f));
    shape.setPoint(3, position + sf::Vector2f(0.f, -unit / 2.f));
}


non_initializable_tile::non_initializable_tile (char newData, const sf::Vector2f& newPosition)
{
    shape = sf::ConvexShape(4);
    shape.setOutlineThickness(-3.f);
    data = newData;
    position = newPosition;
    this->setShape(newData);

    // constructing 2:1 Aspect Ratio Tile for Isometric Projection
    shape.setPoint(0, position + sf::Vector2f(-unit, 0.f));
    shape.setPoint(1, position + sf::Vector2f(0.f, unit / 2.f));
    shape.setPoint(2, position + sf::Vector2f(unit, 0.f));
    shape.setPoint(3, position + sf::Vector2f(0.f, -unit / 2.f));
}


void_tile::void_tile ()
{
    // Void tile has nothig to initialize 
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
{
    // Do Nothing
}


void void_tile::onMouseClick (char newData)
{
    // Do Nothing
}


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
    // Do Nothing
}


bool tile::isVoid ()
{
    return false;
}


bool void_tile::isVoid ()
{
    return true;
}