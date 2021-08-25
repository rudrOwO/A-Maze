#include "card.h"
extern sf::RenderWindow window;
extern float cardDrawStartY;


const std::unordered_map<std::string, int> Card::tokenToActionType = {
    {"move",  Action::move},
    {"turn",  Action::turn},
    {"write", Action::write},
    {"state", Action::setState}
};


Card::Card ():
    dataToActionQueue(9),
    cursor("->", firaCode, fontSize + 1),
    cardBox({width, 0.f}),
    startPosition(window.getSize().x * (4.f / 5.f), cardDrawStartY),
    red(Palette::colors.at('7').first),
    grey(Palette::colors.at('*').first),
    blue_grey(Palette::colors.at('5').first)
    
{
    cardBox.setPosition(startPosition);
    cardBox.setFillColor(blue_grey);
    cursor.setPosition(startPosition + sf::Vector2f(10.f, 0.f));
    cursor.setStyle(sf::Text::Style::Bold);
}


void Card::push_line (bool isScopped, const std::pair<std::string, std::string>& token)
{
    code.push_back({false, false, {"", ""}, {0, 0}, sf::Text("", firaCode, fontSize)});

    Line &currentLine = code.back();

    currentLine.isLocked = (token.first != "");
    currentLine.drawToScreen.setPosition(startPosition + sf::Vector2f(offSet, (code.size() - 1) * (fontSize + lineSpace)));

    if (currentLine.isLocked) {
        currentLine.drawToScreen.setStyle(sf::Text::Style::Bold);
        currentLine.drawToScreen.setCharacterSize(fontSize + 1);
    }

    formatCode(code.size() - 1, isScopped, token);
    cardBox.setSize({width, cardBox.getSize().y + fontSize + lineSpace});
}


void Card::formatCode (int lineIndex, bool isScopped, const std::pair<std::string, std::string>& token)
{
    Action pushAction;
    
    if (token.first != "if" and token.first != "")
        pushAction.type = tokenToActionType.at(token.first);

    if (token.first == "move" or token.first == "turn")
        pushAction.argument = std::stoi(token.second);
    else if (token.first == "write" or token.first == "state" or token.first == "if")
        pushAction.argument = token.second[0];
    
    Line &currentLine = code[lineIndex];

    currentLine.isScopped = isScopped;
    currentLine.token = token;
    currentLine.action = pushAction;
    currentLine.drawToScreen.setString(token.first + " " + token.second);
    
    if (currentLine.isScopped)
        currentLine.drawToScreen.setPosition({startPosition.x + offSet + indentation, currentLine.drawToScreen.getPosition().y});
}


void Card::onKeyPress (sf::Event& event)
{
    switch (event.key.code) {
        case sf::Keyboard::Down:
            if (lineEditorIndex < code.size() - 1)
                ++lineEditorIndex;

    }
}


void Card::compileCode ()
{
    for (const auto& line : code) {
        if (line.token.first == "if")
            currentScope = line.action.argument - '0';

        else if (line.token.first != "") {
            if (not line.isScopped) {
                for (int i = 0; i < 9; ++i)
                    dataToActionQueue[i].push_back({ tokenToActionType.at(line.token.first), line.action.argument });

            } else {
                dataToActionQueue[currentScope].push_back({ tokenToActionType.at(line.token.first), line.action.argument });
            }
        }
    }
}


const std::deque<Action>& Card::getActionQueue (char data) const
{
    if (data == '*')
        data = '8';

    return dataToActionQueue[data - '0'];
}


void Card::draw ()
{
    window.draw(cardBox);
    window.draw(cursor);
    
    for (const auto& line : code)
        window.draw(line.drawToScreen);
}