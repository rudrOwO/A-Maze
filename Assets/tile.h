#pragma once
#include <SFML/Graphics.hpp>
#include <vector>


/*************************
*   * FOR BLANK TILE     *
*    - FOR VOID TILE     *
*    [0 ~ 7] FOR DATA    *
* ! FOR DESTINATION TILE *
**************************/


class Tile
{
protected:
    char data;
    sf::Vector2f position;
    std::vector<sf::ConvexShape> shapes;

    Tile () = default;
    Tile (char newData, const sf::Vector2f& newPosition);

public:
    static constexpr float unit = 60.f, height = 15.f;   

    // getters
    char getData () const;
    sf::Vector2f getPosition () const;

    // setters
    void setData (char newData);
    void setShape (char newData);

    bool isVoid ();
    bool isDestination ();
    
    // pure virtual functions
    virtual void onMouseClick (char newData) = 0;
    virtual void draw () = 0;
};



class Initializable_tile : public Tile
{
public:
    Initializable_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void draw () override;
};



class Non_initializable_tile : public Tile
{
private:
    sf::RectangleShape lock;

public:
    Non_initializable_tile (char newData, const sf::Vector2f& newPosition, sf::Texture* lockTexture);

    void onMouseClick (char newData) override;
    void draw () override;
};
 


class Void_tile : public Tile
{
public:
    Void_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void draw () override;
};