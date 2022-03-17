#ifndef _TOOL_HPP_
#define _TOOL_HPP_

#include <iostream>
#include <string>
#include "Item.hpp"

using namespace std;

class Tool : public Item{
    protected:
        int durability;
    
    public:
        //CTOR, CCTOR, operator=, DTOR
        Tool();
        Tool(int id, string name, string type, int durability);
        Tool(const Tool& tool);
        Tool& operator=(const Tool& tool);
        virtual ~Tool();

        //Getter
        int getDurability();

        //Setter
        void setDurability(int d);

        virtual void show();

};

#endif