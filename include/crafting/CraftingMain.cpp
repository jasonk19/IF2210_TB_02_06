#include <filesystem>
#include "../NonTool.hpp"
#include "../Tool.hpp"
#include "Crafting.hpp"
using namespace std;

int main(){
    Crafting c;
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    Item::readItemConfig(itemConfigPath);
    for (const auto &entry : filesystem::directory_iterator(configPath + "/recipe")) {
        if(!entry.is_directory()){
            Recipe r(entry.path().string());
            c.addRecipe(r);
        }
    }
    /* Menampilkan resep-resep
    for(const auto& x : c.getRecipes()){
        x.displayRecipe();
    }*/

    // Membuat item-item
    Item* stoneSword1 = new Tool(STONE_SWORD, "STONE_SWORD", "-", 3);
    Item* stoneSword2 = new Tool(*dynamic_cast<Tool*>(stoneSword1));
    Item* oakPlank = new NonTool(OAK_PLANK, "OAK_PLANK",  "PLANK", 2);
    Item* sprucePlank = new NonTool(SPRUCE_PLANK, "SPRUCE_PLANK", "PLANK", 1);
    Item* stick = new NonTool(STICK, "STICK", "-", 1);

    // Memperbaiki Tool
    c.setItem(stoneSword1, 0, 0);
    c.setItem(stoneSword2, 2, 2);
    c.showCrafting();
    Item* resultSword = c.craft();
    cout << '\n';
    c.showCrafting();
    cout << "Hasil\n";
    resultSword->show();
    cout << '\n';

    // Membuat Barang
    c.setItem(oakPlank, 0, 0);
    c.setItem(sprucePlank, 1, 0);
    c.setItem(stick, 2, 0);

    // Menampilkan kondisi meja dan melakukan craft
    c.showCrafting();
    Item* result = c.craft();
    cout << "Hasil\n";
    result->show();
    cout << '\n';
    c.showCrafting();

    return 0;
}