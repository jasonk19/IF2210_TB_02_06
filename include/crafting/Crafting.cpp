#include "Crafting.hpp"

Crafting::Crafting(){
    for(int i=0; i < 3; i++){
        for(int j=0; j < 3; j++){
            crafting_table[i][j] = NULL;
        }
    }
}

void Crafting::addRecipe(Recipe r){
    this->recipe.push_back(r);
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

Item* Crafting::craftSimulate(){
    
}