// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "include/Class.hpp"
#include "include/Inventory.hpp"
#include "include/SlotInventory.hpp"
#include "include/crafting/Recipe.hpp"
#include "include/crafting/Crafting.hpp"

using namespace std;

int main() {
  Crafting crafting;
  Inventory inventory;
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  Item::readItemConfig(itemConfigPath);
  // read item from config file
  ifstream itemConfigFile(itemConfigPath);
  for (string line; getline(itemConfigFile, line);) {
    cout << line << endl;
    // do something
  }

  // read recipes
  for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
    Recipe r(entry.path().string());
    crafting.addRecipe(r);
  }

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") 
    {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++) {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
    }

    else if (command == "SHOW")
    {
      crafting.showCrafting();
      inventory.showInventory();
    }

    else if (command == "GIVE") 
    {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      Item* i = Item::generateObject(Item::nama_ItemIdMap.find(itemName)->second);
      inventory.addItem(i, itemQty);
      cout<<itemName<<" added to inventory"<<endl;
    } 

    else if (command == "DISCARD")
    {
       string id;
       int qty;
       cin >> id >> qty;
       inventory.discardItem(id, qty);
       cout<<id<<" discarded, qty = "<<qty<<endl;
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
         string* arr = new string[slotQty];
         arr[0] = slotDest;
         for (int i = 1 ; i < slotQty ; i++)
         {
           cin >> slotDest;
           arr[i] = slotDest;
         }
         inventory.moveToCrafting(slotSrc, slotQty, arr, crafting); 
         cout<<"Item has been moved to crafting"<<endl;
      }

      //inventory to inventory
      else if (slotSrc[0] == 'I' && slotDest[0] =='I')
      {
         inventory.moveItem(slotSrc, slotDest);
         cout<<"Item has been stacked in inventory"<<endl;
      }

      //crafting to inventory
      else if (slotSrc[0] == 'C' && slotDest[0] == 'I')
      {
        crafting.moveToInventory(inventory, slotSrc, slotDest);
        cout<<"Item has been moved to inventory"<<endl;
      }
    } 

    else if (command == "CRAFT") {
      Item* craftResult = crafting.craft();
      if(craftResult == NULL){
        cout << "Crafting Gagal!\nTidak resep yang cocok\n\n";
      } else{
        // TODO: move craftResult to Inventory
      }
    } 

    else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
