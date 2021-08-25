#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <deque>
#include <string>
#include "action.h"
#include "palette.h"
extern sf::RenderWindow window;
extern sf::Font firaCode;


class Card
{
private:
    char currentScope;
    unsigned int fontSize = 20;
    float width = window.getSize().x / 5.f, lineSpace = 2.f;
    struct Line
    {
        bool isLocked, isScopped;
        std::string token;
        int arg;
        sf::Text drawToScreen;
    };
    int lineEditorPos = 0;
    std::vector<Line> code;
    std::vector<std::deque<Action>> dataToActionQueue; 
    sf::Color grey, blue_grey, red;
    sf::RectangleShape cardBox;
    sf::RectangleShape lineEditorBox;
    sf::Vector2f startPosition;
    static const std::unordered_map<std::string, int> tokenToActionType;

public:    
    Card ();
    void onKeyPress (sf::Event& event);
    void draw ();
    void interpret ();
    void push_line (bool isLocked, bool isScopped, const std::string& token, int arg = 0);
    const std::deque<Action>& getActionQueue (char data) const;
};