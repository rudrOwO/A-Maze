#include "tile.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


char tile::getData () const
{
    return data;
}


float tile::getScale () const
{
    return scale;
}
