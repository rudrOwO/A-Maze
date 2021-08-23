#pragma once
#include <SFML/Graphics.hpp>
#include "bot.h"
#include <vector>
#include <unordered_map>
#include <deque>
#include <string>
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Card
{
private:
    char currentScope;
    struct Command
    {
        bool isLocked, isScopped;
        Bot::Action action;
        sf::Text drawToScreen;
    };
    int lineEditor = 0;
    std::vector<Command> code;
    std::unordered_map<char, std::deque<Bot::Action>> dataToActionQ; 
    static const std::unordered_map<std::string, int> tokenToActionType;

public:    
    Card ();
    void onKeyPress (sf::Event& event);
    void draw ();
    void interpret ();
    void push_line (bool isLocked, bool isScopped, const std::string& token, int arg = 0);
};