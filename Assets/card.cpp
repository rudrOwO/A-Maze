#include "card.h"


const std::unordered_map<std::string, int> Card::tokenToActionType = {
    {"move",  Action::move},
    {"turn",  Action::turn},
    {"write", Action::write},
    {"state", Action::setState}
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
