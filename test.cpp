#include <iostream>

class parent
{
public:
    parent () = default;
    
    parent (int a)
    {
        
    }

    virtual void test ()
    {
        std::cout << "Parent" << std::endl;
    }
};


class child : public parent
{
public:
    child (int a)
    {
        
    }

    void test () override
    {
        std::cout << "Child" << std::endl;
    }
    
};


int main ()
{
    parent* ara[2];
    ara[0] = new parent(1);
    ara[1] = new child(1);
    
    ara[0]->test();
    ara[1]->test();
}