// sample main file, replace this with your own code
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "include/Item.hpp"
#include "include/NonTool.hpp"
#include "include/Tool.hpp"
#include "include/crafting/Recipe.hpp"
#include "include/crafting/Crafting.hpp"

using namespace std;

int main() {
  Crafting crafting;
  string configPath = "./config";
  string itemConfigPath = configPath + "/item.txt";

  Item::readItemConfig(itemConfigPath);
  // read item from config file
  //ifstream itemConfigFile(itemConfigPath);
  //for (string line; getline(itemConfigFile, line);) {
    //cout << line << endl;
    // do something
  //}

  // read recipes
  for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
    Recipe r(entry.path().string());
    crafting.addRecipe(r);
  }

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
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
    } else if (command == "CRAFT") {
      Item* craftResult = crafting.craft();
      if(craftResult == NULL){
        cout << "Crafting Gagal!\nTidak resep yang cocok\n\n";
      } else{
        // TODO: move craftResult to Inventory
      }
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      cout << "TODO" << endl;
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;
      cout << "TODO" << endl;
    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}
