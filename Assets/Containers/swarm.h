#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../bot.h"

// Game over on:
// Collission; Out of Bounds

class Swarm
{
private:
    std::vector<Bot> bots;
    std::vector<std::vector<sf::Texture*>> botTextures; 
    Tile_matrix& tileMap; 
    
public:
    Swarm (const std::vector<std::string>& botMatrix, Tile_matrix& tileMap);
    void draw ();
    Bot& operator[] (int index);
};