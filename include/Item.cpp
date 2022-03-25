#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include <fstream>

Mapping<string,int> Item::nama_ItemIdMap;
Mapping<int,Item*> Item::itemId_ItemMap;
Mapping<int,string> Item::itemId_rawTypeMap;
Mapping<string,int> Item::rawType_rawIdMap;

void Item::readItemConfig(string configFile){
    ifstream config(configFile);
    int id;
    string name, type, toolnontool;
    while(config >> id >> name >> type >> toolnontool){
        Item::nama_ItemIdMap.setContent(name, id);
        if(toolnontool == "TOOL"){
            Item::itemId_ItemMap.setContent(id, new Tool(id, name, toolnontool, 10));
        } else{
            Item::itemId_ItemMap.setContent(id, new NonTool(id, name, toolnontool, 1));
        }
        if(type != "-"){
            Item::itemId_rawTypeMap.setContent(id, type);
            if(!Item::rawType_rawIdMap.isIn(type)){
                int typeId = 101 + Item::rawType_rawIdMap.getSize();
                Item::rawType_rawIdMap.setContent(type, typeId);
                Item::itemId_rawTypeMap.setContent(typeId, type);
            }
        }
    }

    config.close();
}

Item* Item::generateObject(int itemId){
    Item* temp = Item::itemId_ItemMap.getContent(itemId);
    if(temp->isA<Tool>()){
        return new Tool(*dynamic_cast<Tool*>(temp));
    } else{
        return new NonTool(*dynamic_cast<NonTool*>(temp));
    }
}

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
    // cout<<"Item Destroyed"<<endl;
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
