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
    cardBox({width, 0.f}),
    startPosition(window.getSize().x * (4.f / 5.f), cardDrawStartY),
    red(Palette::colors.at('7').first),
    grey(Palette::colors.at('*').first),
    blue_grey(Palette::colors.at('5').first)
    
{
    cardBox.setPosition(startPosition);
    cardBox.setFillColor(blue_grey);
}


void Card::push_line (bool isScopped, const std::pair<std::string, std::string>& token)
{
    bool isLocked = (token.first != "");

    
    
    Action pushAction;
    
    if (token.first != "if" and token.first != "")
        pushAction.type = tokenToActionType.at(token.first);

    if (token.first == "move" or token.first == "turn")
        pushAction.argument = std::stoi(token.second);
    else if (token.first == "write" or token.first == "state" or token.first == "if")
        pushAction.argument = token.second[0];
    
    code.push_back({ isLocked, isScopped, token, pushAction});
    cardBox.setSize({width, cardBox.getSize().y + fontSize + lineSpace});
}


void Card::onKeyPress (sf::Event& event)
{
    
}


void Card::interpret ()
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
    
    for (const auto& line : code)
        window.draw(line.drawToScreen);
}
