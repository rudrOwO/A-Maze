#include <SFML/Graphics.hpp>
#include <string>
#include <map>


class palette
{
public:
    sf::Font dataFont;
    sf::Text colorData;

public:
    static const std::map<char, std::pair<sf::Color, sf::Color>> colors;
    
    palette ();
};