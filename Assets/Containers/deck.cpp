#include "deck.h"


Deck::Deck ():
    deckColor_light(0x607d8bff),
    deckColor_dark(0x34515eff)

{}


void Deck::interpretAll ()
{
    for (const auto& card : cards)
        card.second->interpret();
    
    interpretStat = true;
}


Card* Deck::operator[] (int cardID)
{
    return cards[cardID];
}


bool Deck::isInterpreted ()
{
    return interpretStat;
} 