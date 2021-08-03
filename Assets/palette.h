#include <SFML/Graphics.hpp>
#include <map>


class palette
{
private:

public:
    static const std::map<char, std::pair<sf::Color, sf::Color>> colors;
    
    palette ();
};