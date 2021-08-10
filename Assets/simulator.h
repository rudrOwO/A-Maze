#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class Simulator 
{
private:
    float unit = 40.f;
    int buttonCount = 4, status = 0, currentIndex = 0;
    sf::Vector2f origin;
    sf::Color bgColor;
    std::vector<sf::RectangleShape> buttons;
    std::vector<std::string> textureFileSequence {"play", "pause", "restart", "menu"};
    //std::vector<sf::Texture> textureDrawSequence;

public:
    enum {paused, running};

    Simulator ();

    static int getStatus ();
    bool onMouseClick ();
    void draw ();
};