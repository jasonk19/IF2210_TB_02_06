#include "Crafting.hpp"

Crafting::Crafting(){
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            crafting_table[i][j] = NULL;
        }
    }
}

void Crafting::addRecipe(Recipe r){
    this->recipes.push_back(r);
}

void Crafting :: showCrafting(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            Item* temp = crafting_table[i][j];
            if(temp == NULL){
                cout << "[    ]";
            }
            else if (temp->isA<Tool>()){
                Tool T = *dynamic_cast<Tool*>(temp);
                cout << "[" << T.getName() << "," << T.getDurability() << "] ";
            }
            else{
                NonTool NT = *dynamic_cast<NonTool*>(temp);
                cout << "[" << NT.getName() << "," << NT.getQuantity() << "] ";
            }
        }
        cout << endl;
    }
}

// jangan lupa hasilnya didelete, kecuali jika dipakai
Item* Crafting::craftSimulate(){
    Item* res;

    vector<vector<ItemID> > itemInCraftTable;
    for(int i=0; i < 3; i++){
        vector<ItemID> rowItem;
        for(int j=0; j < 3; j++){
            if(this->crafting_table[i][j] != NULL){
                rowItem.push_back((ItemID)this->crafting_table[i][j]->getId());
            } else{
                rowItem.push_back(NO_ITEM);
            }
        }
        itemInCraftTable.push_back(rowItem);
    }
    Recipe current(itemInCraftTable);
    for(const auto& recipe : this->recipes){
        if(current.match(recipe)){
            Item* temp = Item::itemId_ItemMap.find(recipe.getResultId())->second;
            if(temp->isA<Tool>()){
                res = new Tool(*dynamic_cast<Tool*>(temp));
            } else{
                res = new NonTool(*dynamic_cast<NonTool*>(temp));
                dynamic_cast<NonTool*>(res)->setQuantity(recipe.getResultCount());
            }
            break;
        }
    }

    return res;
}