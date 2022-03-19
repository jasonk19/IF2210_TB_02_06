#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include "SlotInventory.hpp"
#include "crafting/Crafting.hpp"
#include <bits/stdc++.h>
using namespace std;

int convertIDtoInt(string ID);
int getRow(int integer);
int getCol(int integer);

class Inventory {
    protected:
        SlotInventory** InvenContainer;
        const int sizeRow = 3;
        const int sizeCol = 9;
        int quantity;
    public:
        Inventory();
        Inventory(const Inventory& inventory);
        Inventory& operator=(const Inventory& Inventory);
        virtual ~Inventory();
        void moveItem(string IDsrc, string IDdest);
        void moveToCrafting(string IDslotInventory, int N, string* IDcraftdest);

        void addItem(Item* item, int quantity);
        void removeItem(Item* item, int quantity);

};

#endif
