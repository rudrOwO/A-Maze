#pragma once
#include "../Assets/Containers/tile_matrix.h"
#include "../Assets/Containers/swarm.h"
// #include "../Assets/Containers/deck.h"

#include "../Assets/tile.h"
#include "../Assets/card.h"
#include "../Assets/bot.h"

#include "../Assets/palette.h"
#include "../Assets/simulator.h"


struct Asset_collection
{
    Tile_matrix* tileMap;
    Swarm* swarm;
    // Deck deck*

    Palette* colorGuide;
    Simulator* simulator;
};