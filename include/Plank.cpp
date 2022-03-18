#include "Plank.hpp"

Plank::Plank() : NonTool(-1, "Unknown Plank", "Plank", 0){}

Plank::Plank(int id, int quantity) : NonTool(id, "-", "Plank", quantity)
{
    switch(id)
    {
        case 4 : name = "Oak Plank";break;
        case 5 : name = "Spruce Plank";break;
        case 6 : name = "Birch Plank";break;
        default : name = "Unknown Plank";
    }
}

Plank::Plank(const Plank& plank) : NonTool(plank){}

Plank& Plank::operator=(const Plank& plank)
{
    NonTool::operator=(plank);
    return *this;
}

Plank::~Plank()
{
    // cout<<"Plank Destroyed"<<endl;
}