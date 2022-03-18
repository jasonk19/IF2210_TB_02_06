#include "Crafting.hpp"

void Crafting :: showCrafting(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            Item temp = crafting_table[i][j];
            Tool T = temp;
            if (temp.isA<Tool>()){
                Tool T = temp;
                cout << "[" << T.getName() << "," << T.getDurability() << "] ";
            }
            else{
                NonTool NT = temp;
                cout << "[" << NT.getName() << "," << NT.getQuantity() << "] ";
            }
        }
        cout << endl;
    }
}