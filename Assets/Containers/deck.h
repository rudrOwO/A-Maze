#pragma once
#include <SFML/Graphics.hpp>
#include "../card.h"
#include <fstream>
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Deck
{
private:
    float width = window.getSize().x / 5.f, height = window.getSize().y;
    sf::Color deckColor_light, deckColor_dark;
    sf::Text deckInfo;
    sf::RectangleShape deckShape;
    std::vector<Card*> cards;
    
public:
    Deck (std::ifstream& levelFile); 
};