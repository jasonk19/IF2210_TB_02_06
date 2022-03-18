#include "Pickaxe.hpp"

Pickaxe::Pickaxe() : Tool(-1, "Unknown Pickaxe", "-", 0)
{
    material = "Unknown Material";
}

Pickaxe::Pickaxe(int id, int durability) : Tool(id, "-", "-", durability)
{
    switch(id)
    {
        case 13 : material = "Wooden"; name = "Wooden Pickaxe"; break;
        case 14 : material = "Stone"; name = "Stone Pickaxe" ; break;
        case 15 : material = "Iron"; name = "Iron Pickaxe"; break;
        case 16 : material = "Diamond"; name = "Diamond Pickaxe" ; break;
        default : material = "Unknown Material"; name = "Unknown Pickaxe" ;
    }
}

Pickaxe::Pickaxe(const Pickaxe& p) : Tool(p)
{
    this->material = p.material;
}

Pickaxe& Pickaxe::operator=(const Pickaxe& p)
{
    Tool::operator=(p);
    this->material = p.material;
    return *this;
}

Pickaxe::~Pickaxe()
{
    // cout<<"Pickaxe Destroyed"<<endl;
}

void Pickaxe::show()
{
    Tool::show();
    cout<<"Material : "<<material<<endl;
}