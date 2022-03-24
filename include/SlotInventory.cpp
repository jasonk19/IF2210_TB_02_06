#include "SlotInventory.hpp"

SlotInventory::SlotInventory() {
  this->id = -1;
  this->slotcontainer = NULL;
  this->quantity = 0;
}

SlotInventory::SlotInventory(Item* item, int id, int quantity) {
  this->id = id;
  this->slotcontainer = item;
  this->quantity = quantity;
}

SlotInventory::~SlotInventory() {
  // delete slot
}

void SlotInventory::setSlot(Item* item, int id, int quantity) {
  this->id = id;
  this->slotcontainer = item;
  this->quantity = quantity;
}

int SlotInventory::getId() {
  return this->id;
}

int SlotInventory::getQuantity() {
  return this->quantity;
}

int SlotInventory::getEmptyQuantity(){
    return (64 - quantity);
}

Item* SlotInventory::getItem() {
  return this->slotcontainer;
}

string SlotInventory::getNameFromSlotItem(){
    return this->slotcontainer[0].getName();
}

string SlotInventory::getTypeFromSlotItem(){
    return this->slotcontainer[0].getType();
}

void SlotInventory::setEmptySlot() {
  this->id = -1;
  this->slotcontainer = NULL;
  this->quantity = 0;
}

void SlotInventory::addQuantity(int quantity) {
  this->quantity = this->quantity + quantity;
}

void SlotInventory::reduceQuantity(int quantity) {
  this->quantity = this->quantity - quantity;
}

void SlotInventory::addItemToSlot(Item* item, int Quantity){
    int CurrentQuantity = Quantity + this->quantity;
    this->slotcontainer = item;
    this->quantity = CurrentQuantity;
}

void SlotInventory::removeItem(int QuantityToRemove){
    int CurrentQuantity = this->quantity - QuantityToRemove;
    this->quantity = CurrentQuantity;
    if (this->quantity == 0)
    {
        this->setEmptySlot();
    }
    else if (this->quantity < 0)
    {
        throw "error bang";
    }

}
