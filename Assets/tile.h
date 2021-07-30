/**********************
* INTERFACE FOR TILE *
**********************/
class tile
{
private:
    char data;
    float scale;   // used by the whole engine for setting scale
    
public:
    char getData () const;
    float getScale () const;

};


/*****************************************************************
 *    NOTE THAT "EDITABLE" IMPLIES EDITABILITY BY THE PLAYER     *
 * IN THE PROGRAMMING STAGE; MACHINES CAN ALWAYS WRITE TO A TILE *
 *****************************************************************/

class editable_tile : public tile
{
    editable_tile ();
};


class non_editable_tile : public tile
{
    non_editable_tile ();
};
 
 
class void_tile : public tile
{
    void_tile ();
};