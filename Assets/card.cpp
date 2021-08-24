#include "card.h"


const std::unordered_map<std::string, int> Card::tokenToActionType = {
    {"move",  Action::move},
    {"turn",  Action::turn},
    {"write", Action::write},
    {"state", Action::setState}
};


Card::Card ():
    dataToActionQueue(9) ,
    grey(Palette::colors.at('*').first),
    blue_grey(Palette::colors.at('5').first)
    
{}


void Card::push_line(bool isLocked, bool isScopped, const std::string& token, int arg)
{
    code.push_back({ isLocked, isScopped, token, arg, sf::Text(token, firaCode, arg) });
}


void Card::onKeyPress (sf::Event& event)
{
    
}


void Card::interpret ()
{
    for (const auto& line : code) {
        if (line.token == "if")
            currentScope = line.arg - '0';

        else if (line.token != "") {
            if (not line.isScopped) {
                for (int i = 0; i < 9; ++i)
                    dataToActionQueue[i].push_back({ tokenToActionType.at(line.token), line.arg });

            } else {
                dataToActionQueue[currentScope].push_back({ tokenToActionType.at(line.token), line.arg });
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
    
}
