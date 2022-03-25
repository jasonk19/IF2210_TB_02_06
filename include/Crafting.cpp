#include "Tool.hpp"
#include "NonTool.hpp"
#include "Crafting.hpp"
#include "Exception.hpp"

int getRowCraft(int integer){
    return (int)(integer/3);
}

int getColCraft(int integer){
    return (integer % 3);
}

Item* Crafting::getItem(int i, int j) const{
    return this->crafting_table[i][j];
}

bool Crafting::isCompatible(Item* itm, int i, int j){
    if (itm == NULL)
    {
        return true;
    }
    
    if(this->crafting_table[i][j] != NULL){
        Item* tableItem = crafting_table[i][j];
        if(itm->getId() == tableItem->getId()){
            if(itm->isA<Tool>()){
                throw Exception("Source Item is a Tool and destination is not empty");
            } else{
                return true;
            }
        } else{
            throw Exception("Source and destination not same type");
        }
    }

    return true;
}

void Crafting::changeItemQty(int i, int j, int changeQuantity){
    if(this->crafting_table[i][j] != NULL){
        if(this->crafting_table[i][j]->isA<NonTool>()){
            NonTool* NT = dynamic_cast<NonTool*>(this->crafting_table[i][j]);

            NT->setQuantity(NT->getQuantity()+changeQuantity);
            if(NT->getQuantity() <= 0){
                delete this->crafting_table[i][j];
                this->crafting_table[i][j] = NULL;
            }
        } else if(changeQuantity < 0){  // Jika NonTool dan changeQuantity nya < 0
            delete this->crafting_table[i][j];
            this->crafting_table[i][j] = NULL;
        }
    }
}

void Crafting::setItem(Item* itm, int i, int j){
    if (itm == NULL)
    {
        this->crafting_table[i][j] = NULL;
    }
    else{
        if(this->crafting_table[i][j] != NULL){
            delete crafting_table[i][j];
        }

        if(itm->isA<Tool>()){
            this->crafting_table[i][j] = new Tool(*dynamic_cast<Tool*>(itm));
        } else{
            NonTool* NT = new NonTool(*dynamic_cast<NonTool*>(itm));
            NT->setQuantity(1);
            this->crafting_table[i][j] = NT;
        }
    }
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

    vector<vector<int> > itemInCraftTable;
    int nonToolCount = 0;
    vector<Item*> toolsInCraft;

    for(int i=0; i < 3; i++){
        vector<int> rowItem;
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
    if(current.getRowEff() == 0) return NULL;
    
    int highestScore = 0;
    for(const auto& recipe : this->recipes){
        int currentScore = current.match(recipe);
        if(currentScore > highestScore){
            res = Item::generateObject(recipe.getResultId());
            if(res->isA<NonTool>()){
                dynamic_cast<NonTool*>(res)->setQuantity(recipe.getResultCount());
            }
            highestScore = currentScore;
            if(highestScore == 2) break;
        }
    }
    return res;
}

Item* Crafting::craft(){
    Item* craftRes = this->craftSimulate();
    if(craftRes == NULL)
        throw Exception("Crafting failed! No matching recipe!");

    
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
    return craftRes;
}

void Crafting :: moveToInventory(Inventory& inventory, string IDCraftsrc, string IDinvendest){
   
    int rowCraft = getRowCraft(convertIDtoInt(IDCraftsrc));
    int colCraft = getColCraft(convertIDtoInt(IDCraftsrc));
    int idInvent = inventory.getIdFromString(IDinvendest);
    
    Item* item = this->getItem(rowCraft, colCraft);
    // Kemaungkinan Kasus
    // 1. crafting_table kosong -> gabisa move, output pesan
    if (item == NULL){
        throw Exception("Move Failed! Tidak ada item pada slot crafting " + IDCraftsrc);
    }
    else{
        Item* temp = NULL;
        if(item->isA<Tool>()){
            temp = new Tool(*dynamic_cast<Tool*>(item));
        } else{
            temp = new NonTool(*dynamic_cast<NonTool*>(item));
        }
        SlotInventory& inventorySlot = inventory.getSlot(idInvent);;

        // 2. inventory kosong -> bisa move
        if (inventorySlot.getQuantity() == 0){
            // lakukan pemindahan barang lgsg
            inventorySlot.addItemToSlot(temp,1);
            changeItemQty(rowCraft, colCraft, -1);
        }
        else{
            bool sameType = inventorySlot.getNameFromSlotItem() == temp->getName();

            // 3. inventory keisi item sama -> cek jumlah itemnya < 64 ga?
            if (sameType){
                // check jumlah item kalo nontool, kalo tool gabisa dipindah
                if (temp->isA<Tool>()){
                    throw Exception("Move Failed! Tidak bisa memindahkan item, Tool tidak bisa ditumpuk");
                }
                else{
                    if (inventorySlot.getEmptyQuantity() >= 1){
                        inventorySlot.addItemToSlot(temp,1);
                        changeItemQty(rowCraft, colCraft, -1);
                    }
                    else{
                        throw Exception("Move Failed! Slot inventory " + IDinvendest + " sudah penuh");
                    }
                }
            }
            // 4. inventory keisi item beda -> gabisa move, output pesan
            else{
                throw Exception("Move Failed! Tidak bisa memindahkan item, tipe item tidak cocok dengan tujuan");
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
