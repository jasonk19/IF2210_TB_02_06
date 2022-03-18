#include "Stone.hpp"

Stone::Stone() : NonTool(-1, "Unknown Stone", "Stone", 0){}

Stone::Stone(int id, int quantity) : NonTool(id, "-", "Stone", quantity)
{
    switch(id)
    {
        case 8 : name = "Cobblestone";break;
        case 9 : name = "Blackstone";break;
        default : name = "Unknown Stone";break;
    }
}

Stone::Stone(const Stone& stone) : NonTool(stone) {}

Stone& Stone::operator=(const Stone& stone)
{
    NonTool::operator=(stone);
    return *this;
}

Stone::~Stone()
{
    // cout<<"Stone Destroyed"<<endl;
}