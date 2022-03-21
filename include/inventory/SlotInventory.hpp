// Class buat nyimpan item pada satu slot inventory

#ifndef _SLOTINVENTORY_HPP_
#define _SLOTINVENTORY_HPP_

#include <bits/stdc++.h>
#include "../Item.hpp"
#include "../Tool.hpp"
#include "../NonTool.hpp"
using namespace std;

class SlotInventory
{
  protected:
    Item* slotcontainer;
    int id;
    int quantity;
  public:
    SlotInventory();
    SlotInventory(Item* item, int id, int quantity);
    ~SlotInventory();

    void setSlot(Item* item, int id, int quantity);

    int getId();
    int getQuantity();
    Item* getItem();

    void setEmptySlot();

    void addQuantity(int quantity);
    void reduceQuantity(int quantity);

};

#endif
