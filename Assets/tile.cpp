#include "tile.h"
#include <map>

extern std::map<char, std::pair<sf::Color, sf::Color>> palette;



initializable_tile::initializable_tile (char newData, const sf::Vector2f& newPosition)
{
    shape = sf::ConvexShape(4);
    data = newData;
    position = newPosition;
    this->setShape(newData);

    // constructing 2:1 Aspect Ratio Tile for Isometric Projection
    
}




char tile::getData () const
{
    return data;
}


float tile::getScale () const
{
    return scale;
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


void tile::setShape (char newData)
{
    shape.setFillColor(palette[newData].first);
    shape.setOutlineColor(palette[newData].second);
}


bool tile::isVoid ()
{
    return false;
}


bool void_tile::isVoid ()
{
    return true;
}