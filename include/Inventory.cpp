#include "Inventory.hpp"

int convertIDtoInt(string ID){
    int temp;
    for (int i = 1; i < ID.size(); i++){
        temp += ID[i] * pow(10,ID.size() - 1 - i);
    }
    return temp;
}

int getRow(int integer){
    return (int)(integer/9);
}

int getCol(int integer){
    return (integer % 9);
}

Inventory::Inventory()
{
    for (int i = 0; i < sizeRow; i++){
        for (int j = 0; j < sizeCol; j++){
            InvenContainer[i][j] = SlotInventory();
        }
    }
    this->quantity = 0;
}

Inventory::Inventory(const Inventory& inventory)
{
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeCol; j++)
        {
            this->InvenContainer[i][j] = inventory.InvenContainer[i][j];
        }
    }
    this->quantity = inventory.quantity;
}

Inventory& Inventory::operator=(const Inventory& inventory)
{
    for (int i = 0; i < sizeRow; i++)
    {
        for (int j = 0; j < sizeCol; j++)
        {
            this->InvenContainer[i][j] = inventory.InvenContainer[i][j];    
        }
    }
    this->quantity = inventory.quantity;
    return *this;
}


Inventory::~Inventory()
{
    // cout << "Inventory has been Destroyed" << endl;
}

void Inventory::moveItem(string IDsrc, string IDdest){
    int RowSRC = getRow(convertIDtoInt(IDsrc)), ColSRC = getCol(convertIDtoInt(IDsrc));
    int RowDEST = getRow(convertIDtoInt(IDdest)), ColDEST = getCol(convertIDtoInt(IDdest));
    if ((this->InvenContainer[RowSRC][ColSRC].getNameFromSlotItem() == this->InvenContainer[RowDEST][ColDEST].getNameFromSlotItem()) && (this->InvenContainer[RowSRC][ColSRC].getTypeFromSlotItem() == this->InvenContainer[RowDEST][ColDEST].getTypeFromSlotItem()) && ((this->InvenContainer[RowSRC][ColSRC].getItemInfo())->isA<NonTool>()) && ((this->InvenContainer[RowDEST][ColDEST].getItemInfo())->isA<NonTool>())){
        // Move
        int QuantityToMove;
        if (this->InvenContainer[RowSRC][ColSRC].getQuantity() <= this->InvenContainer[RowDEST][ColDEST].getEmptyQuantity()){

            // Move seluruh Item dari src ke dest
            QuantityToMove = this->InvenContainer[RowSRC][ColSRC].getQuantity();
        }
        else{
            // Move sebagian Item
            QuantityToMove = this->InvenContainer[RowDEST][ColDEST].getEmptyQuantity();
        }
        // Add
        this->InvenContainer[RowDEST][ColDEST].addItemToSlot(this->InvenContainer[RowSRC][ColSRC].getItemInfo(), QuantityToMove);
        // Remove
        this->InvenContainer[RowSRC][ColSRC].removeItem(QuantityToMove);
    }

    else{
        cout << "Maaf kedua item berbeda\n" << endl;
    }
}

void Inventory::moveToCrafting(string IDslotInventory, int N, string* IDcraftdest, Crafting table){
    // belum gan
    int Row = getRow(convertIDtoInt(IDslotInventory)), Col = getCol(convertIDtoInt(IDslotInventory)); int ColCraftTable = getCol(N-1), RowCraftTable = getRow(N-1);
    int RowCraftDest, ColCraftDest;
    if (this->InvenContainer[Row][Col].getQuantity() >= N){
        if (N < 9){
            for (int i = 0; i < RowCraftTable; i++){
                for (int j = 0; j < ColCraftTable; j++){
                    N--;
                    RowCraftDest = getRow(convertIDtoInt(IDcraftdest[N]));
                    ColCraftDest = getCol(convertIDtoInt(IDcraftdest[N]));
                    // Add item to crafting
                    table.setItem(this->InvenContainer[Row][Col].getItemInfo(), i, j);
                }
            }
            // Remove Item yang telah di add ke crafting
            // this->InvenContainer[Row][Col].removeItem(N);
        }
    }
}

bool Inventory::containItem(Item* item) {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->InvenContainer[i][j].getItemInfo();
            if (temp->getName() == item->getName() && this->InvenContainer[i][j].getQuantity() < 64) {
                return true;
            }
        }
    }
    return false;
}

void Inventory::addItem(Item* item, int quantity) {
    int id = 0;
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            if (quantity != 0) {
                Item* temp = this->InvenContainer[i][j].getItemInfo();
                if (this->InvenContainer[i][j].getQuantity() == 0 && !containItem(item)) {
                    this->InvenContainer[i][j] = SlotInventory(item, quantity, id);
                    quantity = 0;
                } else if (temp->getName() == item->getName()) {
                    if (temp->isA<NonTool>()) {
                        if (this->InvenContainer[i][j].getQuantity() + quantity <= 64) {
                            this->InvenContainer[i][j].addItemToSlot(item, quantity);
                            quantity = 0;
                        } else {
                            int quantityLeft = this->InvenContainer[i][j].getQuantity() + quantity;
                            quantityLeft -= 64;
                            quantity -= quantityLeft;
                            this->InvenContainer[i][j].addItemToSlot(item, quantity);
                        }
                    }
                }
            } else {
                return;
            }
            id++;
        }
    }
}

void Inventory::discardItem(string id, int quantity) {
    int idSlot = convertIDtoInt(id);

    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->InvenContainer[i][j].getItemInfo();
            if (this->InvenContainer[i][j].getIDslot() == idSlot) {
                if (temp->isA<NonTool>()) {
                    if (quantity <= this->InvenContainer[i][j].getQuantity()) {
                        this->InvenContainer[i][j].removeItem(quantity);
                    }
                    if (this->InvenContainer[i][j].getQuantity() <= 0) {
                        this->InvenContainer[i][j] = SlotInventory();
                    }
                }
            }
        }
    }
}

// Export inventory
void Inventory::exportInventory(string outputPath) {
    ofstream outputFile(outputPath);

    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->InvenContainer[i][j].getItemInfo();
            if (temp->isA<NonTool>()) {
                outputFile << temp->getId() << ":" << this->InvenContainer[i][j].getQuantity() << endl;
            } else {
                Tool* t = dynamic_cast<Tool*>(temp);
                outputFile << t->getId() << ":" << t->getDurability() << endl;
            }
        }
    }
}
