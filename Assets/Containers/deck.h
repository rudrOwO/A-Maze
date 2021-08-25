#pragma once
#include <SFML/Graphics.hpp>
#include "../card.h"
#include "../palette.h"
#include "../action.h"
#include <vector>
#include <map>
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Deck
{
private:
    bool compileStat = false;
    unsigned int fontSize = 22;
    float width = window.getSize().x / 5.f;
    sf::Vector2f startPosition;
    sf::Color green, red;
    std::string displayMessage;
    sf::Text displayMessageText;
    std::vector<sf::RectangleShape> deckShapes;
    std::map<char, Card*> cards;
    std::map<char, Card*>::iterator nowEditing;
    
public:
    Deck (); 
    void onKeyPress (sf::Event& event);
    void draw ();
    void compileAll ();
    bool isCompiled ();
    Card* operator[] (int cardID);

    friend void loadLevel (int level);
};