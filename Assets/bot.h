#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <utility>
#include "Containers/tile_matrix.h"
#include "../Engine/isometry.h"
/* STATE COMMAND IS EFFECTiVE IMMEDIATELY */


class Bot
{
public:
    struct Action 
    { 
        enum { move, turn, write, setState };
        int type, argument; 
    };


private:
    static constexpr float unit = 55.f;
    int direction; 
    char state, data;
    Tile_matrix& tileMap;
    const std::vector<sf::Texture*>& texturePointers;
    std::vector<sf::RectangleShape> sprites;
    sf::Vector2f position;
    sf::Vector2i logicalPosition;
    std::deque<Action> actionQueue = {
        {Action::move, 3},
        {Action::turn, 1},
        {Action::move, 1},
        {Action::write, '3'}
    };

    void (*isometricMove[4]) (sf::Vector2f&, int) = {
        isometricIncrementX, 
        isometricIncrementY, 
        isometricDecrementX, 
        isometricDecrementY
    };
    
    void read ();
    void move ();
    void turn ();
    void write (char newData);
    void setState (char newState);
    std::deque<Action> getActionQueue (int state, int data); // From the Interpreter


public:
    Bot (sf::Vector2i logicalPosition, char state, int direction, const std::vector<sf::Texture*>& texturePointers, Tile_matrix& tileMap);
    ~Bot ();

    bool isBotDEAD ();
    bool isBotDONE ();
    void pollActionQueue ();  // continuously check actionQueue for actions
    void draw ();
    const sf::Vector2i& getLogicalPosition ();
};