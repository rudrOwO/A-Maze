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
    sf::Color grey, blue_grey;
    sf::RectangleShape cardBox;
    sf::RectangleShape lineEditorBox;
    static const std::unordered_map<std::string, int> tokenToActionType;


public:    
    Card ();
    void onKeyPress (sf::Event& event);
    void draw ();
    void interpret ();
    void push_line (bool isLocked, bool isScopped, const std::string& token, int arg = 0);
    const std::deque<Action>& getActionQueue (char data) const;
};