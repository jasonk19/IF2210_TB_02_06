#include "../Tool.hpp"
#include "../NonTool.hpp"
#include "Crafting.hpp"

int getRowCraft(int integer){
    return (int)(integer/3);
}

int getColCraft(int integer){
    return (integer % 3);
}

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

void Crafting :: moveToInventory(Inventory& inventory, string IDCraftsrc, string IDinvendest){
   
    int rowCraft = getRowCraft(convertIDtoInt(IDCraftsrc));
    int colCraft = getColCraft(convertIDtoInt(IDCraftsrc));
    int rowInventory = getRowInven(convertIDtoInt(IDinvendest));
    int colInventory = getColInven(convertIDtoInt(IDinvendest));
    Item* temp = this->getItem(rowCraft,colCraft);
    // Kemaungkinan Kasus
    // 1. crafting_table kosong -> gabisa move, output pesan
    if (temp == NULL){
        cout << "Tidak ada item pada slot crafting " << IDCraftsrc << endl;
    }
    else{
        Item* inventorySlot; // belum ada method akses inventory


        // 2. inventory kosong -> bisa move
        if (inventorySlot == NULL){
            // lakukan pemindahan barang lgsg
            inventorySlot = temp;
            this->setItem(NULL,rowCraft,colCraft);
        }
        else{
            bool sameType = inventorySlot->getName() == temp->getName();

            // 3. inventory keisi item sama -> cek jumlah itemnya < 64 ga?
            if (sameType){
                // check jumlah item kalo nontool, kalo tool gabisa dipindah
                if (temp->isA<Tool>()){
                    cout << "Tidak bisa memindahkan item, Tool tidak bisa ditumpuk" << endl;
                }
                else{
                    NonTool* NT = dynamic_cast<NonTool*>(inventorySlot);
                    if (NT->getQuantity() < 64){
                        //move item (belum bisa akses inventory)
                    }
                    else{
                        cout << "Slot inventory " << IDinvendest << " sudah penuh" << endl;
                    }
                }
                
            }
            // 4. inventory keisi item beda -> gabisa move, output pesan
            else{
                cout << "Tidak bisa memindahkan item, tipe item tidak cocok";
            }
        }
    }
}
    

Crafting::~Crafting(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(this->crafting_table[i][j] != NULL)
                delete this->crafting_table[i][j];
        }
    }
}
