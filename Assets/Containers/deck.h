#pragma once
#include <SFML/Graphics.hpp>
#include "../card.h"
#include "../action.h"
#include <vector>
#include <unordered_map>
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Deck
{
private:
    bool interpretStat = false;
    float width = window.getSize().x / 5.f, height = window.getSize().y;
    sf::Color deckColor_light, deckColor_dark;
    sf::Text deckInfo[2];
    sf::RectangleShape deckShapes[3];
    std::unordered_map<char, Card*> cards;
    
public:
    Deck (); 
    void onKeyPress (sf::Event& event);
    void draw ();
    void interpretAll ();
    bool isInterpreted ();
    Card* operator[] (int cardID);

    friend void loadLevel (int level);
};