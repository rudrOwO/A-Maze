#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <utility>
#include "Containers/tile_matrix.h"
#include "Containers/deck.h"
#include "../Engine/isometry.h"
#include "action.h"


class Bot
{
private:
    static constexpr float unit = 55.f;
    static void (*isometricMove[4]) (sf::Vector2f&, int);
    int direction; 
    char state, data;
    Tile_matrix* &tileMap;
    Deck* &deck;
    const std::vector<sf::Texture*>& texturePointers;
    std::vector<sf::RectangleShape> sprites;
    sf::CircleShape stateIndicatorCircle;
    sf::Text stateIndicatorText;
    sf::Vector2f position;
    sf::Vector2i logicalPosition;
    std::deque<Action> actionQueue;
    
    void read ();
    void move ();
    void turn ();
    void write (char newData);
    void setState (char newState);

public:
    Bot (sf::Vector2i logicalPosition, char state, int direction, const std::vector<sf::Texture*>& texturePointers, Tile_matrix* &tileMap, Deck* &deck);
    ~Bot ();

    bool isBotDEAD ();
    bool isBotDONE ();
    void pollActionQueue ();  
    void draw ();
    const sf::Vector2i& getLogicalPosition ();
};