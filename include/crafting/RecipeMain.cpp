#include "Recipe.hpp"

int main(){
    // compile dari folder main src langsung, bukan dari sini
    Item::readItemConfig("config/item.txt");
    for(const auto& x : Item::nama_ItemIdMap){
        cout << x.first << ' ' << x.second << '\n';
    }
    cout << '\n';
    Recipe r("./config/recipe/IRON_AXE.txt");
    r.displayRecipe();

    return 0;
}