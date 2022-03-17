#include "Item.hpp"

Item::Item()
{
    id = -1;
    name = "Unknown";
    type = "Unknown";
}

Item::Item(int id, string name, string type)
{
    this->id = id;
    this->name = name;
    this->type = type;
}

Item::Item(const Item& item)
{
    this->id = item.id;
    this->name = item.name;
    this->type = item.type;
}

Item& Item::operator=(const Item& item)
{
    this->id = item.id;
    this->name = item.name;
    this->type = item.type;
    return *this;
}

Item::~Item()
{
    cout<<"Item Destroyed"<<endl;
}

int Item::getId()
{
    return id;
}

string Item::getName()
{
    return name;
}

string Item::getType()
{
    return type;
}

void Item::setId(int id)
{
    this->id = id;
}

void Item::setName(string name)
{
    this->name = name;
}

void Item::setType(string type)
{
    this->type = type;
}