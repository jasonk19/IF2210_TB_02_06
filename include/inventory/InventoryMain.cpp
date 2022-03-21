#include "Inventory.hpp"
#include <iostream>

using namespace std;

int main() {
  Inventory i;
  Item* oakPlank = new NonTool(OAK_PLANK, "OAK_PLANK",  "PLANK", 2);
  Item* sprucePlank = new NonTool(SPRUCE_PLANK, "SPRUCE_PLANK", "PLANK", 1);
  Item* stick = new NonTool(STICK, "STICK", "-", 1);
  Item* sword = new Tool(WOODEN_SWORD, "WOODEN_SWORD", "-", 10);

  i.showInventory();

  i.addItem(oakPlank, 10);
  i.addItem(sprucePlank, 20);
  i.addItem(stick, 30);

  i.showInventory();

  i.addItem(oakPlank, 20);

  i.showInventory();

  i.addItem(stick, 50);

  i.showInventory();

  i.discardItem("I0", 12);

  i.showInventory();

  cout << i.getTotalQuantity(stick) << endl;

  i.addItem(sword);

  i.showInventory();

  i.discardItem("I1", 20);

  i.showInventory();

  i.addItem(sprucePlank, 40);

  i.showInventory();

  i.addItem(sprucePlank, 120);

  i.showInventory();

  i.addItem(stick, 50);

  i.showInventory();

  i.addItem(stick, 80);

  i.showInventory();

  cout << "Export Inventory" << endl;
  i.testExport();

  return 0;
}