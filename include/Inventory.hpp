#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include "SlotInventory.hpp"
#include "Crafting.hpp"
#include <string>
#include <fstream>
using namespace std;

class Crafting;

int convertIDtoInt(string ID);

class Inventory {
  protected:
    SlotInventory* InvenContainer;
  public:
    Inventory();

    // Getter
    int getIdFromString(string id);
    int getTotalQuantity(Item* item);
    SlotInventory& getSlot(int id);

    bool containItem(Item* item);
    void addItem(Item* item, int quantity = 1);
    void discardItem(string id, int quantity);
    void useTool(string id);
    void moveItem(string IDsrc, string IDdest);
    void moveToCrafting(string IDslotInventory, int N, string* IDcraftdest, Crafting& table);

    // Show Inventory
    void showInventory();

    // Export Inventory
    void testExport();
    void exportInventory(string outputPath);
};

#endif
