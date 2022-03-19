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
    if ((this->InvenContainer[RowSRC][ColSRC].getNameFromSlotItem() == this->InvenContainer[RowDEST][ColDEST].getNameFromSlotItem()) && (this->InvenContainer[RowSRC][ColSRC].getTypeFromSlotItem() == this->InvenContainer[RowDEST][ColDEST].getTypeFromSlotItem())){
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

void Inventory::moveToCrafting(string IDslotInventory, int N, string* IDcraftdest){
    // belum gan
}

void Inventory::addItem(Item* item, int quantity) {
    int id = 0;
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->InvenContainer[i][j].getItemInfo();
            if (this->InvenContainer[i][j].getQuantity() == 0) {
                this->InvenContainer[i][j] = SlotInventory(item, quantity, id);
            } else if (temp->getId() == item->getId()) {
                if (temp->isA<NonTool>()) {
                    this->InvenContainer[i][j].addQuantity(quantity);
                } else {
                    if (j < sizeCol - 1) {
                        this->InvenContainer[i][j+1] = SlotInventory(item, quantity, id+1);
                    } else {
                        if (i < sizeRow - 1) {
                            this->InvenContainer[i+1][0] = SlotInventory(item, quantity, id+1);
                        }
                    }
                }
            }
            id++;
        }
    }
}

