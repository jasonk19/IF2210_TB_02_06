#include "Recipe.hpp"

int main(){
    // compile dari folder main src langsung, bukan dari sini
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
    Recipe r1("./config/recipe/WOODEN_AXE.txt");
    Recipe r2("./config/recipe/WOODEN_AXE.txt");
    Recipe r3("./config/recipe/SPRUCE_PLANK.txt");
    // Wooden axe with mixed plank type
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
    r1.displayRecipe();
    r5.displayRecipe();
    //cout << r5.getRowEff() << 'x' << r5.getColEff() << '\n';

    cout << "r1 dan r2 apakah sama: " << r1.match(r2) << '\n';
    cout << "r1 dan r3 apakah sama: " << r1.match(r3) << '\n';
    cout << "r1 dan r4 apakah sama: " << r1.match(r4) << '\n';
    cout << "r1 dan r5 apakah sama: " << r1.match(r5) << '\n';

    return 0;
}