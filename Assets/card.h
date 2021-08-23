#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <deque>
#include <string>
#include "action.h"
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Card
{
private:
    char currentScope;
    const float fontSize = 20.f;
    struct Line
    {
        bool isLocked, isScopped;
        std::string token;
        int arg;
        sf::Text drawToScreen;
    };
    int lineEditor = 0, lockSize = 0;
    std::vector<Line> code;
    std::vector<std::deque<Action>> dataToActionQueue; 
    static const std::unordered_map<std::string, int> tokenToActionType;

public:    
    Card ();
    void onKeyPress (sf::Event& event);
    void draw ();
    void interpret ();
    void push_line (bool isLocked, bool isScopped, const std::string& token, int arg = 0);
    const std::deque<Action>& getActionQueue (char data) const;
};