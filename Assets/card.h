#pragma once
#include <SFML/Graphics.hpp>
#include "bot.h"
#include <vector>
#include <deque>
#include <string>
#include <fstream>
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Card
{
private:
    struct line
    {
        std::string command;
        int argument;
        sf::Text drawable;
    };
    
    int linePointer = 0;
    std::vector<line> code;
    std::vector<bool> isLocked;
    std::vector<std::deque<Bot::Action>> actionMap; 

public:    
    Card ();
    void onKeyPress (sf::Event& event);
};