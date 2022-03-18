#include "Sword.hpp"

Sword::Sword() : Tool(-1, "Unknown Sword", "-", 0)
{
    material = "Unknown Material";
}

Sword::Sword(int id, int durability) : Tool(id, "-", "-", durability)
{
    switch(id)
    {
        case 21 : material = "Wooden"; name = "Wooden Sword"; break;
        case 22 : material = "Stone"; name = "Stone Sword" ; break;
        case 23 : material = "Iron"; name = "Iron Sword"; break;
        case 24 : material = "Diamond"; name = "Diamond Sword" ; break;
        default : material = "Unknown Material"; name = "Unknown Sword" ;
    }
}

Sword::Sword(const Sword& sword) : Tool(sword)
{
    this->material = sword.material;
}

Sword& Sword::operator=(const Sword& sword)
{
    Tool::operator=(sword);
    this->material = sword.material;
    return *this;
}

Sword::~Sword()
{
    // cout<<"Sword Destroyed"<<endl;
}

void Sword::show()
{
    Tool::show();
    cout<<"Material : "<<material<<endl;
}