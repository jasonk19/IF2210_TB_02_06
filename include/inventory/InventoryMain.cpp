#include "Inventory.hpp"
#include <iostream>

using namespace std;

int main() {
  Inventory i;
  Item* oakPlank = new NonTool(OAK_PLANK, "OAK_PLANK",  "PLANK", 2);
  Item* sprucePlank = new NonTool(SPRUCE_PLANK, "SPRUCE_PLANK", "PLANK", 1);
  Item* stick = new NonTool(STICK, "STICK", "-", 1);
  Item* stoneSword1 = new Tool(STONE_SWORD, "STONE_SWORD", "-", 10);
  Item* stoneSword2 = new Tool(*dynamic_cast<Tool*>(stoneSword1));

  i.showInventory();

  i.addItem(oakPlank, 10);
  i.addItem(sprucePlank, 20);
  i.addItem(stick, 30);

  i.showInventory();

  i.addItem(sprucePlank, 60);
  i.discardItem("I0", 10);

  i.showInventory();

  i.addItem(sprucePlank, 60);
  i.addItem(oakPlank, 120);
  i.addItem(stoneSword1, 1);
  i.addItem(stoneSword2, 1);

  i.showInventory();

  i.useTool("I6");

  i.showInventory();

  i.testExport();

  return 0;
}