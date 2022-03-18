#include "Axe.hpp"

Axe::Axe() : Tool(-1, "Unknown Axe", "-", 0)
{
    material = "Unknown Material";
}

Axe::Axe(int id, int durability) : Tool(id, "-", "-", durability)
{
    switch(id)
    {
        case 17 : material = "Wooden"; name = "Wooden Axe"; break;
        case 18 : material = "Stone"; name = "Stone Axe" ; break;
        case 19 : material = "Iron"; name = "Iron Axe"; break;
        case 20 : material = "Diamond"; name = "Diamond Axe" ; break;
        default : material = "Unknown Material"; name = "Unknown Axe" ;
    }
}

Axe::Axe(const Axe& axe) : Tool(axe)
{
    this->material = axe.material;
}

Axe& Axe::operator=(const Axe& axe)
{
    Tool::operator=(axe);
    this->material = axe.material;
    return *this;
}

Axe::~Axe()
{
    // cout<<"Axe Destroyed"<<endl;
}

void Axe::show()
{
    Tool::show();
    cout<<"Material : "<<material<<endl;
}