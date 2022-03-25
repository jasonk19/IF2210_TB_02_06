// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "./include/Exception.hpp"
#include "include/Class.hpp"

using namespace std;

int main()
{
  Crafting crafting;
  Inventory inventory;
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  Item::readItemConfig(itemConfigPath);
  // read item from config file
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);)
  {
    cout << line << endl;
    // do something
  }

  // read recipes
  for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe"))
  {
    Recipe r(entry.path().string());
    crafting.addRecipe(r);
  }

  // sample interaction
  string command;
  while (cin >> command)
  {
    try
    {
      if (command == "SHOW")
      {
        crafting.showCrafting();
        inventory.showInventory();
      }

      else if (command == "GIVE")
      {
        string itemName;
        int itemQty;
        cin >> itemName >> itemQty;
        if(!Item::nama_ItemIdMap.isIn(itemName)) throw Exception("Invalid Item Name!");

        Item *i = Item::generateObject(Item::nama_ItemIdMap.getContent(itemName));
        inventory.addItem(i, itemQty);
        cout << itemName << " added to inventory" << endl;
      }

      else if (command == "DISCARD")
      {
        string id;
        int qty;
        cin >> id >> qty;
        inventory.discardItem(id, qty);
        cout << id << " discarded, qty = " << qty << endl;
      }

      else if (command == "MOVE")
      {
        string slotSrc;
        int slotQty;
        string slotDest;
        cin >> slotSrc >> slotQty >> slotDest;
        // inventory to crafting
        if (slotSrc[0] == 'I' && slotQty >= 1 && slotDest[0] == 'C')
        {
          string *arr = new string[slotQty];
          arr[0] = slotDest;
          for (int i = 1; i < slotQty; i++)
          {
            cin >> slotDest;
            arr[i] = slotDest;
          }
          inventory.moveToCrafting(slotSrc, slotQty, arr, crafting);
          cout << "Item has been moved to crafting" << endl;
        }

        // inventory to inventory
        else if (slotSrc[0] == 'I' && slotDest[0] == 'I')
        {
          inventory.moveItem(slotSrc, slotDest);
          cout << "Item has been stacked in inventory" << endl;
        }

        // crafting to inventory
        else if (slotSrc[0] == 'C' && slotDest[0] == 'I')
        {
          crafting.moveToInventory(inventory, slotSrc, slotDest);
          cout << "Item has been moved to inventory" << endl;
        }
      }

      else if (command == "CRAFT")
      {
        Item *craftResult = crafting.craft();
        if (craftResult->isA<NonTool>())
        {
          inventory.addItem(craftResult, dynamic_cast<NonTool *>(craftResult)->getQuantity());
        }
        else
        {
          inventory.addItem(craftResult);
        }
        cout << "Crafting Success !" << endl;
      }

      else if (command == "USE")
      {
        string id;
        cin >> id;
        inventory.useTool(id);
        cout << "Item used" << endl;
      }

      else if (command == "EXPORT")
      {
        string filename;
        cin >> filename;
        inventory.exportInventory(filename);
        cout << "File exported to " << filename << endl;
      }

      else
      {
        throw Exception("Invalid command");
      }
    }
    catch (Exception e)
    {
      cout << e.getMessage() << '\n';
    }
  }
  return 0;
}
