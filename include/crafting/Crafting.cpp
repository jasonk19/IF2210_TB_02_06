#include "../Tool.hpp"
#include "../NonTool.hpp"
#include "Crafting.hpp"

Item* Crafting::getItem(int i, int j) const{
    return this->crafting_table[i][j];
}

void Crafting::setItem(Item* itm, int i, int j){
    this->crafting_table[i][j] = itm;
}

vector<Recipe> Crafting::getRecipes() const{
    return this->recipes;
}

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
                Tool* T = dynamic_cast<Tool*>(temp);
                cout << "[" << T->getName() << "," << T->getDurability() << "] ";
            }
            else{
                NonTool* NT = dynamic_cast<NonTool*>(temp);
                cout << "[" << NT->getName() << "," << NT->getQuantity() << "] ";
            }
        }
        if(i == 1){ // Tampilan apa yang akan dihasilkan jika memanggil command craft
                cout << "\t\t===> ";
                Item* resultCraft = craftSimulate();
                if(resultCraft == NULL){
                    cout << "[    ]";
                } else if(resultCraft->isA<Tool>()){
                    Tool* T = dynamic_cast<Tool*>(resultCraft);
                    cout << "[" << T->getName() << "," << T->getDurability() << "] ";
                } else{
                    NonTool* NT = dynamic_cast<NonTool*>(resultCraft);
                    cout << "[" << NT->getName() << "," << NT->getQuantity() << "] ";
                }
                delete resultCraft;
        }
        cout << endl;
    }
}

// jangan lupa hasilnya didelete, kecuali jika dipakai
Item* Crafting::craftSimulate(){
    Item* res = NULL;

    vector<vector<ItemID> > itemInCraftTable;
    int nonToolCount = 0;
    vector<Item*> toolsInCraft;

    for(int i=0; i < 3; i++){
        vector<ItemID> rowItem;
        for(int j=0; j < 3; j++){
            Item* temp = this->crafting_table[i][j];
            if(temp != NULL){
                rowItem.push_back((ItemID)temp->getId());
                if(temp->isA<Tool>()){
                    toolsInCraft.push_back(temp);
                } else{
                    nonToolCount++;
                }
            } else{
                rowItem.push_back(NO_ITEM);
            }
        }
        itemInCraftTable.push_back(rowItem);
    }
    // Handle memperbaiki kombinasi dua Tool bertipe sama
    if(toolsInCraft.size() == 2 && nonToolCount == 0){
        if(toolsInCraft[0]->getId() == toolsInCraft[1]->getId()){
            int totalDurability = dynamic_cast<Tool*>(toolsInCraft[0])->getDurability() + dynamic_cast<Tool*>(toolsInCraft[1])->getDurability();
            totalDurability = totalDurability > 10 ? 10 : totalDurability;
            return new Tool(toolsInCraft[0]->getId(), toolsInCraft[0]->getName(),
                            toolsInCraft[0]->getType(), totalDurability);
        }
    }
    Recipe current(itemInCraftTable);
    for(const auto& recipe : this->recipes){
        if(current.match(recipe)){
            res = Item::generateObject(recipe.getResultId());
            if(res->isA<NonTool>()){
                dynamic_cast<NonTool*>(res)->setQuantity(recipe.getResultCount());
            }
            break;
        }
    }

    return res;
}

Item* Crafting::craft(){
    Item* craftRes = this->craftSimulate();
    if(craftRes != NULL){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                Item* current = this->crafting_table[i][j];
                if(current != NULL){
                    if(current->isA<NonTool>()){
                        NonTool* NT = dynamic_cast<NonTool*>(current);
                        if(NT->getQuantity() == 1){
                            delete current;
                            crafting_table[i][j] = NULL;
                        } else{
                            NT->setQuantity(NT->getQuantity() - 1);
                        }
                    } else{
                        delete current;
                        crafting_table[i][j] = NULL;
                    }
                }
            }
        }
    }
    return craftRes;
}

Crafting::~Crafting(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->crafting_table[i][j] != NULL)
                delete this->crafting_table[i][j];
        }
    }
}