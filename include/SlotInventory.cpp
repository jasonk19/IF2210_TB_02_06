#include "SlotInventory.hpp"

SlotInventory::SlotInventory()
{
    quantity = 0;
    IDslot = -1;
    for (int i = 0; i < capacity; i++){
        slotContainer[i].setId(-1);
        slotContainer[i].setName("Unknown");
        slotContainer[i].setType("Unknown");
    } 
}


SlotInventory::SlotInventory(Item* slotContainer, int quantity, int IDslot){
    this->IDslot = IDslot;
    if (quantity <= capacity){
        this->quantity = quantity;
        this->slotContainer = slotContainer;
    }
    else
    {
        cout << "Maaf quantity yang dimasukkan melebihi kapasitas";
    }
}

SlotInventory::SlotInventory(const SlotInventory& slotinventory){
    this->IDslot = slotinventory.IDslot;
    if (quantity <= capacity){
        this->quantity = slotinventory.quantity;
        this->slotContainer = slotinventory.slotContainer;
    }
    else
    {
        cout << "Maaf quantity yang dimasukkan melebihi kapasitas";
    }
}

SlotInventory::~SlotInventory(){
    // cout << "SlotInventory has been Destroyed" << endl;
}

int SlotInventory::getIDslot(){
    return this->IDslot;
}

int SlotInventory::getQuantity(){
    return this->quantity;
}

int SlotInventory::getEmptyQuantity(){
    return (capacity - quantity);
}

void SlotInventory::setIDslot(int IDslot){
    this->IDslot = IDslot;
}

void SlotInventory::setQuantity(int currentQuantity){
    this->quantity = currentQuantity;
}

void SlotInventory::addQuantity(int addQuantity){
    this->quantity += addQuantity;
}