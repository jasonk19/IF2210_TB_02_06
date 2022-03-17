#include "Tool.hpp"

Tool::Tool() : Item(-1, "Unknown", "Unknown")
{
    durability = 0;
}

Tool::Tool(int id, string name, string type, int durability) : Item(id, name, type)
{
    this->durability = durability;
}

Tool::Tool(const Tool& tool)
{
    this->id = tool.id;
    this->name = tool.name;
    this->type = tool.type;
    this->durability = tool.durability;
}

Tool& Tool::operator=(const Tool& tool)
{
    this->id = tool.id;
    this->name = tool.name;
    this->type = tool.type;
    this->durability = tool.durability;
    return *this;
}

Tool::~Tool()
{
    cout<<"Tool Destroyed"<<endl;
}

int Tool::getDurability()
{
    return durability;
}

void Tool::setDurability(int d)
{
    this->durability = d;
}

void Tool::show()
{
    cout<<"ID : "<<id<<endl;
    cout<<"Name : "<<name<<endl;
    cout<<"Type : "<<type<<endl;
    cout<<"Durability : "<<durability<<endl;
}