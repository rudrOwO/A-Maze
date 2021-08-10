#pragma once
#include <SFML/Graphics.hpp>


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
    sf::ConvexShape shape;

    Tile () = default;
    Tile (char newData, const sf::Vector2f& newPosition);

public:
    static constexpr float unit = 60.f;   

    // getters
    char getData () const;
    sf::Vector2f getPosition () const;
    const sf::ConvexShape& getShape () const;

    // setters
    void setData (char newData);
    virtual void setShape (char newData) = 0;

    bool isVoid ();
    bool isDestination ();
    virtual void onMouseClick (char newData) = 0;
};



class Initializable_tile : public Tile
{
public:
    Initializable_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void setShape (char newData) override;
};



class Non_initializable_tile : public Tile
{
protected:
    Non_initializable_tile () = default;

public:
    Non_initializable_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void setShape (char newData) override;
};
 


class Void_tile : public Tile
{
public:
    Void_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void setShape (char newData) override;
};