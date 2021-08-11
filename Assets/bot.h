#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <utility>
#include "Containers/tile_matrix.h"
#include "../Engine/isometry.h"


/* MOVE TURN WRITE STATE 
   STATE COMMAND IS EFFECTiVE IMMEDIATELY */


class Bot
{
public:
    struct Action 
    { 
        enum { move, turn, write, setState };
        int type, argument; 
    };


private:
    int direction, state;
    //const std::vector<sf::Texture*>& texturePointers;
    std::vector<sf::RectangleShape> sprites;
    sf::Vector2f position;
    sf::Vector2i logicalPosition;
    std::deque<Action> actionQueue;

    void (*isometricMove[4]) (sf::Vector2f&, int) = {
        isometricIncrementX, 
        isometricIncrementY, 
        isometricDecrementX, 
        isometricDecrementY
    };
    

public:
    Bot (sf::Vector2i logicalPosition, int state, int direction);
    
    void move (int times);
    void turn (int times);
    void write (int newData);
    void setState (int newState);
    
    void pollActionQueue ();  // continuously check actionQueue for actions
    std::deque<Action> getActionQueue (int state, int data); // From the Interpreter
};