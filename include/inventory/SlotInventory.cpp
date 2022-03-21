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

Item* SlotInventory::getItem() {
  return this->slotcontainer;
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