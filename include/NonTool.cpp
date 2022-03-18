#include "NonTool.hpp"

NonTool::NonTool() : Item(-1, "Unknown", "Unknown")
{
    quantity = 0;
}

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, type)
{
    this->quantity = quantity;
}

NonTool::NonTool(const NonTool& nt) : Item(nt)
{
    this->quantity = nt.quantity;
}

NonTool& NonTool::operator=(const NonTool& nt)
{
    Item::operator=(nt);
    this->quantity = nt.quantity;
    return *this;
}

NonTool::~NonTool()
{
    // cout<<"NonTool Destroyed"<<endl;
}

int NonTool::getQuantity()
{
    return quantity;
}

void NonTool::setQuantity(int q)
{
    quantity = q;
}

void NonTool::show()
{
    cout<<"ID : "<<id<<endl;
    cout<<"Name : "<<name<<endl;
    cout<<"Type : "<<type<<endl;
    cout<<"Quantity : "<<quantity<<endl;
}