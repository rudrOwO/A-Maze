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
    float width = window.getSize().x / 5.f, lineSpace = 10.f, indentation = 25.f;
    struct Line
    {
        bool isLocked, isScopped;
        std::pair<std::string, std::string> token;
        Action action;
        sf::Text drawToScreen;
    };
    int lineEditorIndex = 0;
    sf::Text cursor;
    std::vector<Line> code;
    std::vector<std::deque<Action>> dataToActionQueue; 
    sf::Color grey, blue_grey, red;
    sf::RectangleShape cardBox;
    sf::Vector2f startPosition;
    static const std::unordered_map<std::string, int> tokenToActionType;

    void formatCode (int lineIndex, bool isScopped, const std::pair<std::string, std::string>& token);

public:    
    Card ();
    void onKeyPress (sf::Event& event);
    void draw ();
    void compileCode ();
    void push_line (bool isScopped, const std::pair<std::string, std::string>& token);
    const std::deque<Action>& getActionQueue (char data) const;
};