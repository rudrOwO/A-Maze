#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Simulator 
{
public:
    enum {running, paused, reload, menu};

private:
    static constexpr float unit = 50.f;
    static int status; 
    sf::Vector2f origin;
    sf::Color grey, blue, dark_blue, dark_grey;
    std::vector<sf::RectangleShape> buttons, sprites;
    std::vector<std::string> textureFileSequence {"play", "pause", "restart", "menu"};
    std::vector<sf::Texture*> texturePointerSequence;

public:
    Simulator ();

    static int getStatus ();
    bool onMouseClick ();
    void draw ();
};