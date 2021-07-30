#include "tile.h"
#include <map>

extern std::map<char, std::pair<sf::Color, sf::Color>> palette;



initializable_tile::initializable_tile (char newData, const sf::Vector2f& newPosition)
{
    shape = sf::ConvexShape(4);
    shape.setOutlineThickness(5.f);
    data = newData;
    position = newPosition;
    this->setShape(newData);

    // constructing 2:1 Aspect Ratio Tile for Isometric Projection
    shape.setPoint(0, position + sf::Vector2f(-unit, 0.f));
    shape.setPoint(1, position + sf::Vector2f(0.f, unit / 2.f));
    shape.setPoint(2, position + sf::Vector2f(unit, 0.f));
    shape.setPoint(3, position + sf::Vector2f(0.f, -unit / 2.f));
}


char tile::getData () const
{
    return data;
}


float tile::getUnit () const
{
    return unit;
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


void tile::setData (char newData)
{
    data = newData;
}


void initializable_tile::setShape (char newData)
{
    shape.setFillColor(palette[newData].first);
    shape.setOutlineColor(palette[newData].second);
}


void non_initializable_tile::setShape (char newData)
{
    shape.setFillColor(palette[newData].first);
    shape.setOutlineColor(sf::Color::Black);
}


bool tile::isVoid ()
{
    return false;
}


bool void_tile::isVoid ()
{
    return true;
}