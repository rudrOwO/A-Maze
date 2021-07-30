#include <SFML/Graphics.hpp>
/**********************
* INTERFACE FOR TILE *
**********************/
class tile
{
protected:
    char data;
    float scale = 25.f;   // used by the whole engine for setting scale
    sf::Vector2f position;
    sf::ConvexShape shape;
    
public:
    // getters
    char getData () const;
    float getScale () const;
    const sf::ConvexShape& getShape () const;

    // setters
    void setData (char newData);
    void setShape (char newData);

    virtual bool isVoid ();
    virtual void onMouseClick (char newData) = 0;
};


/*****************************************************************
 *    NOTE THAT "EDITABLE" IMPLIES EDITABILITY BY THE PLAYER     *
 * IN PROGRAMMING STAGE; MACHINES CAN ALWAYS WRITE TO A TILE *
 *****************************************************************/

class initializable_tile : public tile
{
    initializable_tile (char newData, const sf::Vector2f& newPosition);
    void onMouseClick (char newData) override;
};


class non_initializable_tile : public tile
{
    non_initializable_tile (char newData, const sf::Vector2f& newPosition);
    void onMouseClick (char newData) override;
};
 
 
class void_tile : public non_initializable_tile
{
    void_tile (char newData, const sf::Vector2f& newPosition);
    bool isVoid () override;
};