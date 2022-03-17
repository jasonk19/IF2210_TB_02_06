#ifndef _NONTOOL_HPP_
#define _NONTOOL_HPP_

#include <iostream>
#include <string>
#include "Item.hpp"

using namespace std;

class NonTool : public Item{
    protected:
        int quantity;
    
    public:
        //CTOR, CCTOR, operator=, DTOR
        NonTool();
        NonTool(int id, string name, string type, int quantity);
        NonTool(const NonTool& nt);
        NonTool& operator=(const NonTool& nt);
        virtual ~NonTool();

        //Getter
        int getQuantity();

        //Setter
        void setQuantity(int q);

        virtual void show();

};

#endif