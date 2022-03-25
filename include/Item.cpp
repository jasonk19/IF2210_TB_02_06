#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
#include <fstream>

map<string,ItemID> Item::nama_ItemIdMap;
map<ItemID,Item*> Item::itemId_ItemMap;
map<ItemID,string> Item::itemId_rawTypeMap;
map<string,int> Item::rawType_rawIdMap;

void Item::readItemConfig(string configFile){
    ifstream config(configFile);
    int id;
    string name, type, toolnontool;
    while(config >> id >> name >> type >> toolnontool){
        Item::nama_ItemIdMap.insert({name, (ItemID)id});
        if(toolnontool == "TOOL"){
            Item::itemId_ItemMap.insert({(ItemID) id, new Tool(id, name, toolnontool, 10)});
        } else{
            Item::itemId_ItemMap.insert({(ItemID) id, new NonTool(id, name, toolnontool, 1)});
        }
        if(type != "-"){
            Item::itemId_rawTypeMap.insert({(ItemID)id, type});
            if(Item::rawType_rawIdMap.find(type) == Item::rawType_rawIdMap.end()){
                int typeId = 101 + Item::rawType_rawIdMap.size();
                Item::rawType_rawIdMap.insert({type, typeId});
                Item::itemId_rawTypeMap.insert({(ItemID)typeId, type});
            }
        }
    }

    config.close();
}

Item* Item::generateObject(int itemId){
    Item* temp = Item::itemId_ItemMap.find((ItemID)itemId)->second;
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
