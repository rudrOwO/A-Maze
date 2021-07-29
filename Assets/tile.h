                                /**********************
                                 * INTERFACE FOR TILE *
                                 **********************/
class tile
{
private:
    char data;
    float scale;   // critical variable : used by the whole engine for setting scale
    
public:
    virtual char getData () const;
    virtual float getScale () const;
};


class editable_tile : public tile
{
    
};


class non_editable_tile : public tile
{
    
};
 
 
class blank_tile : public tile
{
};