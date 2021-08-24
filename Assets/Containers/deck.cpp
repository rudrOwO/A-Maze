#include "deck.h"


Deck::Deck ():
    deckShapes(3),
    nowEditing(cards.begin()),
    grey(Palette::colors.at('*').first),
    green(Palette::colors.at('3').first),
    blue_grey(Palette::colors.at('5').first),
    red(Palette::colors.at('7').first)

{
    
}


void Deck::onKeyPress (sf::Event& event)
{
    switch(event.key.code) {
        case sf::Keyboard::Left: 
            if (nowEditing != cards.begin())
                --nowEditing;
            break;

        case sf::Keyboard::Right: 
            if (++nowEditing == cards.end())
                --nowEditing;
            break;
        
        default:
            nowEditing->second->onKeyPress(event);
    }
}


void Deck::draw ()
{
    nowEditing->second->draw();
}


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