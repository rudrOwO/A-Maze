#include "bot.h"
extern sf::RenderWindow window;


Bot::Bot (sf::Vector2i logicalPosition, int state, int direction):
    logicalPosition(logicalPosition),
    state(state),
    direction(direction)
    
{
}


void Bot::move (int times)
{
    isometricMove[direction](position, 1);
    
    // update all 4 rectangle sprites
}


void Bot::turn (int times)
{
    direction = (direction + 1) % 4;
    
    // update all 4 rectangle sprites
}


void Bot::write (int newData)
{
    // Swarm needs reference to Tile_matrix
    // set data
    // set shape
}


void Bot::setState (int newState)
{
    state = newState;
    actionQueue.clear();
}