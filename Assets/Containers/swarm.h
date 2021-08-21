#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "../bot.h"

// Game over on: Collission; Out of Bounds

class Swarm
{
private:
    std::vector<Bot*> bots;
    std::vector<std::vector<int>> collisionCheck;
    std::vector<std::vector<sf::Texture*>> botTextures; 
    Tile_matrix& tileMap; 
    
public:
    Swarm (Tile_matrix& tileMap);
    void draw ();
    void pollActions();
    void checkStatus();
    
    friend void loadLevel (int levelNumber);
};