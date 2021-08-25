#include "deck.h"
extern sf::RenderWindow window;

float cardDrawStartY;

Deck::Deck ():
    startPosition(window.getSize().x * (4.f / 5.f), 2.f),
    displayMessage("     < States On Deck >\n \n\n     Now Editing : State  "),
    deckShapes(2),
    green(Palette::colors.at('3').first),
    red(Palette::colors.at('7').first)

{
    displayMessageText.setFont(firaCode);
    displayMessageText.setCharacterSize(Deck::fontSize);
    displayMessageText.setPosition(Deck::startPosition + sf::Vector2f(0.f, 1.f));

    float textHeight = 3 * fontSize + 2 * displayMessageText.getLineSpacing();
    
    deckShapes[0].setPosition(Deck::startPosition);
    deckShapes[0].setSize({width, textHeight});
    deckShapes[0].setFillColor(green);

    deckShapes[1].setPosition(Deck::startPosition + sf::Vector2f(0.f, textHeight));
    deckShapes[1].setSize({width, textHeight * 0.8f});
    deckShapes[1].setFillColor(red);
    
    cardDrawStartY = deckShapes[1].getPosition().y + deckShapes[1].getSize().y + 5.f;
}


void Deck::onKeyPress (sf::Event& event)
{
    switch(event.key.code) {
        case sf::Keyboard::Left: 
            if (nowEditing != cards.begin())
                --nowEditing;
            
            displayMessage.back() = nowEditing->first;
            break;

        case sf::Keyboard::Right: 
            if (++nowEditing == cards.end())
                --nowEditing;

            displayMessage.back() = nowEditing->first;
            break;
        
        default:
            nowEditing->second->onKeyPress(event);
    }
}


void Deck::draw ()
{
    displayMessageText.setString(displayMessage);
    
    window.draw(deckShapes[0]);
    window.draw(deckShapes[1]);
    window.draw(displayMessageText);

    nowEditing->second->draw();
}


void Deck::compileAll ()
{
    for (const auto& card : cards)
        card.second->compileCode();
    
    compileStat = true;
}


Card* Deck::operator[] (int cardID)
{
    return cards[cardID];
}


bool Deck::isCompiled ()
{
    return compileStat;
} 