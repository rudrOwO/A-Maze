#pragma once
#include <SFML/Graphics.hpp>


/*************************
*   * FOR BLANK TILE     *
*    - FOR VOID TILE     *
*    [0 ~ 7] FOR DATA    *
* ! FOR DESTINATION TILE *
**************************/


class tile
{
protected:
    char data;
    sf::Vector2f position;
    sf::ConvexShape shape;

    tile () = default;
    tile (char newData, const sf::Vector2f& newPosition);

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



class initializable_tile : public tile
{
public:
    initializable_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void setShape (char newData) override;
};



class non_initializable_tile : public tile
{
protected:
    non_initializable_tile () = default;

public:
    non_initializable_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void setShape (char newData) override;
};
 


class void_tile : public tile
{
public:
    void_tile (char newData, const sf::Vector2f& newPosition);

    void onMouseClick (char newData) override;
    void setShape (char newData) override;
};