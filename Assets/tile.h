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

    virtual void setData (char newData);
};


/*****************************************************************
 *    NOTE THAT "EDITABLE" IMPLIES EDITABILITY BY THE PLAYER     *
 * IN THE PROGRAMMING STAGE; MACHINES CAN ALWAYS WRITE TO A TILE *
 *****************************************************************/

class editable_tile : public tile
{
    
};


class non_editable_tile : public tile
{
};
 
 
class blank_tile : public tile
{
};