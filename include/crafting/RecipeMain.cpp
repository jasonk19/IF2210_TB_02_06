#include "Recipe.hpp"
#include "../Item.hpp"

int main(){
    // compile dari folder main src langsung, bukan dari sini
    // Membaca config item.txt
    Item::readItemConfig("config/item.txt");
    for(const auto& x : Item::nama_ItemIdMap){
        cout << x.first << ' ' << x.second << ' ';

        if(Item::itemId_rawTypeMap.find(x.second) != Item::itemId_rawTypeMap.end()){
            string rawType = Item::itemId_rawTypeMap.find(x.second)->second;
            cout << "RawType: " << rawType << ' ';
            cout << Item::rawType_rawIdMap.find(rawType)->second << '\n';
        } else{
            cout << '\n';
        }
    }
    cout << '\n';

    // Daftar resep
    Recipe r1("./config/recipe/WOODEN_AXE.txt");
    Recipe r2("./config/recipe/WOODEN_AXE.txt");
    Recipe r3("./config/recipe/SPRUCE_PLANK.txt");

    // Membuat resep dari vector 2D ItemID
    // Wooden axe dengan jenis kay berbeda-beda
    vector<vector<ItemID> > woodenAxeItems;
    woodenAxeItems.push_back({OAK_PLANK, BIRCH_PLANK, NO_ITEM});
    woodenAxeItems.push_back({SPRUCE_PLANK, STICK, NO_ITEM});
    woodenAxeItems.push_back({NO_ITEM, STICK, NO_ITEM});
    Recipe r4(woodenAxeItems);

    // Wooden axe mirrored
    woodenAxeItems.clear();
    woodenAxeItems.push_back({NO_ITEM, BIRCH_PLANK, OAK_PLANK});
    woodenAxeItems.push_back({NO_ITEM, STICK, SPRUCE_PLANK});
    woodenAxeItems.push_back({NO_ITEM, STICK, NO_ITEM});
    Recipe r5(woodenAxeItems);

    // Menampilkan resep
    r1.displayRecipe();

    cout << "r1 dan r2 apakah sama: " << r1.match(r2) << '\n';
    cout << "r1 dan r3 apakah sama: " << r1.match(r3) << '\n';
    cout << "r1 dan r4 apakah sama: " << r1.match(r4) << '\n';
    cout << "r1 dan r5 apakah sama: " << r1.match(r5) << '\n';

    return 0;
}