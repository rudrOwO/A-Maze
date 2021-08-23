#include "card.h"


const std::unordered_map<std::string, int> Card::tokenToActionType = {
    {"move", Bot::Action::move},
    {"turn", Bot::Action::turn},
    {"write", Bot::Action::write},
    {"state", Bot::Action::setState}
};


Card::Card ():
    dataToActionQ(9) 
    
{
    
}


void Card::push_line(bool isLocked, bool isScopped, const std::string& token, int arg)
{
    if (token == "if")
        // exceptional handle
        ;
    else if (token == "")
        // exceptional handle
        ;

}
