#include "bot.h"
#include <iostream>
extern sf::RenderWindow window;


Bot::Bot (sf::Vector2i logicalPosition, char state, int direction, const std::vector<sf::Texture*>& texturePointers, Tile_matrix* &tileMap, Deck* &deck):
    deck(deck),
    tileMap(tileMap),
    texturePointers(texturePointers),
    logicalPosition(logicalPosition),
    state(state),
    direction(direction),
    sprites(4, sf::RectangleShape(sf::Vector2f(Bot::unit, Bot::unit)))
    
{
    position = (*tileMap)[logicalPosition.y][logicalPosition.x]->getPosition() + sf::Vector2f(0.f, 20.f);

    for (int i = 0; i < 4; ++i) {
        sprites[i].setOrigin(Bot::unit / 2.f, Bot::unit / 2.f);    
        sprites[i].setPosition(position);
        sprites[i].setTexture(texturePointers[i]);
    }
}


Bot::~Bot ()
{
    // Will implement destructors later
}


void Bot::pollActionQueue ()
{
    if (actionQueue.empty()) {
        read();
        actionQueue = (*deck)[state]->getActionQueue(data);

    } else {
        Action &currentAction = actionQueue.front();
        
        switch (currentAction.type) {
            case Action::move:
                move(); 
                if (--currentAction.argument == 0)
                    actionQueue.pop_front();
                break;

            case Action::turn:
                turn(); 
                if (--currentAction.argument == 0)
                    actionQueue.pop_front();
                break;

            case Action::write:
                write(currentAction.argument); 
                actionQueue.pop_front();
                break;

            default:
                setState(currentAction.argument); 
        }
    }
}


void Bot::draw ()
{
    window.draw(sprites[direction]);
}


void Bot::read ()
{
    data = (*tileMap)[logicalPosition.y][logicalPosition.x]->getData();
}


void Bot::move ()
{
    // Isometric move on tileMap
    isometricMove[direction](position, 1);

    // Logical position update
    switch (direction) {
        case 0:  ++logicalPosition.x; break;
        case 1:  ++logicalPosition.y; break;
        case 2:  --logicalPosition.x; break;
        default: --logicalPosition.y;
    }

    // Updating position of all 4 sprites 
    for (auto& sprite : sprites) {
        sprite.setPosition(position);
    }
}


void Bot::turn ()
{
    direction = (direction + 1) % 4;
}


void Bot::write (char newData)
{
    (*tileMap)[logicalPosition.y][logicalPosition.x]->setData(newData);
    (*tileMap)[logicalPosition.y][logicalPosition.x]->setShape(newData);
}


void Bot::setState (char newState)
{
    state = newState;
    actionQueue.clear();
}


bool Bot::isBotDEAD ()
{
    return (*tileMap)[logicalPosition.y][logicalPosition.x]->isVoid();
}


bool Bot::isBotDONE ()
{
    return (*tileMap)[logicalPosition.y][logicalPosition.x]->isDestination();
}


const sf::Vector2i& Bot::getLogicalPosition ()
{
    return logicalPosition;
}