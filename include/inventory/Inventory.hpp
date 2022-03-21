#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include "SlotInventory.hpp"
#include <bits/stdc++.h>
#include <string>
#include <fstream>
using namespace std;

class Inventory {
  protected:
    SlotInventory* InvenContainer;
  public:
    Inventory();

    // Getter
    int getIdFromString(string id);
    int getTotalQuantity(Item* item);

    bool containItem(Item* item);
    void addItem(Item* item, int quantity = 1);
    void discardItem(string id, int quantity);

    // Show Inventory
    void showInventory();

    // Export Inventory
    void testExport();
    void exportInventory(string outputPath);
};

#endif
