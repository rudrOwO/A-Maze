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

    // Implement (Static ?) Methods for handling logical change of position

private:
    static constexpr float unit = 55.f;
    int direction, state;
    Tile_matrix& tileMap;
    const std::vector<sf::Texture*>& texturePointers;
    std::vector<sf::RectangleShape> sprites;
    sf::Vector2f position;
    sf::Vector2i logicalPosition;
    std::deque<Action> actionQueue = {
        {Action::move, 3},
        {Action::turn, 1},
        {Action::move, 2}
    };

    void (*isometricMove[4]) (sf::Vector2f&, int) = {
        isometricIncrementX, 
        isometricIncrementY, 
        isometricDecrementX, 
        isometricDecrementY
    };
    

public:
    Bot (sf::Vector2i logicalPosition, int state, int direction, const std::vector<sf::Texture*>& texturePointers, Tile_matrix& tileMap);
    
    void move ();
    void turn ();
    void write (int newData);
    void setState (int newState);
    
    void pollActionQueue ();  // continuously check actionQueue for actions
    void draw ();
    std::deque<Action> getActionQueue (int state, int data); // From the Interpreter
};