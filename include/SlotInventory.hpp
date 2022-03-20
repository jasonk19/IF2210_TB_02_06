// Class buat nyimpan item pada satu slot inventory

#ifndef _SLOTINVENTORY_HPP_
#define _SLOTINVENTORY_HPP_

#include <bits/stdc++.h>
#include "Item.hpp"
#include "Tool.hpp"
#include "NonTool.hpp"
using namespace std;

class SlotInventory
{
    protected:
        Item* slotContainer;
        const int capacity = 64;
        int quantity;
        int IDslot;
    public:
        SlotInventory();
        SlotInventory(Item* slotContainer, int quantity, int IDslot);
        SlotInventory(const SlotInventory& slotinventory);
        SlotInventory& operator=(const SlotInventory& slotinventory);
        virtual ~SlotInventory();

        // Getter
        int getIDslot();
        int getQuantity();
        int getEmptyQuantity();
        Item* getItemInfo();
        string getNameFromSlotItem();
        string getTypeFromSlotItem();

        // Setter
        void setIDslot(int IDslot);
        void setQuantity(int currentQuantity);
        
        // Adder
        void addQuantity(int addQuantity);
        void addItemToSlot(Item* item, int Quantity);

        // Remover
        void removeItem(int QuantityToRemove);
};

#endif
