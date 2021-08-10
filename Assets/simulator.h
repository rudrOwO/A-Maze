#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Simulator 
{
public:
    enum {running, paused, reload, menu};

private:
    float unit = 50.f;
    static int status; 
    int currentIndex = 0;
    sf::Vector2f origin;
    sf::Color bgColor;
    std::vector<sf::RectangleShape> buttons, sprites;
    std::vector<std::string> textureFileSequence {"play", "pause", "restart", "menu"};
    std::vector<sf::Texture*> texturePointerSequence;

public:
    Simulator ();

    static int getStatus ();
    bool onMouseClick ();
    void draw ();
};