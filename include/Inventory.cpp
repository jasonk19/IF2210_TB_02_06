#include "Inventory.hpp"
#include "Exception.hpp"
#include <iostream>

int convertIDtoInt(string ID){
    int temp = 0;
    for (int i = 1; i < ID.size(); i++){
        temp += (ID[i] - '0') * pow(10,ID.size() - 1 - i);
    }
    return temp;
}

Inventory::Inventory() {
  this->InvenContainer = new SlotInventory[27];
}

SlotInventory& Inventory :: getSlot(int id){
  return this->InvenContainer[id];
}
int Inventory::getIdFromString(string id) {
  if (id == "I0") {
    return 0;
  } else if (id == "I1") {
    return 1;
  } else if (id == "I2") {
    return 2;
  } else if (id == "I3") {
    return 3;
  } else if (id == "I4") {
    return 4;
  } else if (id == "I5") {
    return 5;
  } else if (id == "I6") {
    return 6;
  } else if (id == "I7") {
    return 7;
  } else if (id == "I8") {
    return 8;
  } else if (id == "I9") {
    return 9;
  } else if (id == "I10") {
    return 10;
  } else if (id == "I11") {
    return 11;
  } else if (id == "I12") {
    return 12;
  } else if (id == "I13") {
    return 13;
  } else if (id == "I14") {
    return 14;
  } else if (id == "I15") {
    return 15;
  } else if (id == "I16") {
    return 16;
  } else if (id == "I17") {
    return 17;
  } else if (id == "I18") {
    return 18;
  } else if (id == "I19") {
    return 19;
  } else if (id == "I20") {
    return 20;
  } else if (id == "I21") {
    return 21;
  } else if (id == "I22") {
    return 22;
  } else if (id == "I23") {
    return 23;
  } else if (id == "I24") {
    return 24;
  } else if (id == "I25") {
    return 25;
  } else if (id == "I26") {
    return 26;
  } else {
    return -999;
  }
}

int Inventory::getTotalQuantity(Item* item) {
  int total = 0;

  for (int i = 0; i < 27; i++) {
    Item* temp = InvenContainer[i].getItem();
    if (temp != NULL) {
      if (temp->getId() == item->getId()) {
        total += InvenContainer[i].getQuantity();
      }
    }
  }

  return total;
}

void Inventory::moveItem(string IDsrc, string IDdest){
  int indexSrc = convertIDtoInt(IDsrc), indexDest = convertIDtoInt(IDdest);
  if ((this->InvenContainer[indexSrc].getNameFromSlotItem() == this->InvenContainer[indexDest].getNameFromSlotItem()) && (this->InvenContainer[indexSrc].getTypeFromSlotItem() == this->InvenContainer[indexDest].getTypeFromSlotItem()) && ((this->InvenContainer[indexSrc].getItem())->isA<NonTool>()) && ((this->InvenContainer[indexDest].getItem())->isA<NonTool>())){
      // Move
      int QuantityToMove;
      if (this->InvenContainer[indexSrc].getQuantity() <= this->InvenContainer[indexDest].getEmptyQuantity()){

          // Move seluruh Item dari src ke dest
          QuantityToMove = this->InvenContainer[indexSrc].getQuantity();
        // Add
          this->InvenContainer[indexDest].addItemToSlot(this->InvenContainer[indexSrc].getItem(), QuantityToMove);
        // Remove
          this->InvenContainer[indexSrc].removeItem(QuantityToMove);
      }
      else{
          // Move sebagian Item
          throw "error bang";
      }
  }

  else{
      throw Exception("Cannot move Item! Both Items are different");
  }
}

void Inventory::moveToCrafting(string IDslotInventory, int N, string* IDcraftdest, Crafting& table){
  int indexInven = getIdFromString(IDslotInventory);
  int RowCraftDest, ColCraftDest;
  int index = N;
  if (this->InvenContainer[indexInven].getQuantity() >= N){
    if (N < 9){
        for (int i = N-1; i >= 0; i--){
            index--;
            RowCraftDest = getRowCraft(convertIDtoInt(IDcraftdest[index]));
            ColCraftDest = getColCraft(convertIDtoInt(IDcraftdest[index]));
            // Add item to crafting
            table.setItem(this->InvenContainer[indexInven].getItem(), RowCraftDest, ColCraftDest);
        }
        // Remove Item
        this->InvenContainer[indexInven].removeItem(N);
    }
  } else {
    throw Exception("Item's quantity not enough!");
  }
}


bool Inventory::containItem(Item* item) {
  if (item->isA<NonTool>()) {
    for (int i = 0; i < 27; i++) {
      Item* temp = InvenContainer[i].getItem();
      if (temp != NULL) {
        if (temp->getId() == item->getId() && InvenContainer[i].getQuantity() < 64) {
          return true;
        }
      }
    }
  }
  return false;
}

void Inventory::addItem(Item* item, int quantity) {
  int id = 0;
  for (int i = 0; i < 27; i++) {
    if (quantity > 0) {
      Item* temp = this->InvenContainer[i].getItem();
      if (temp == NULL && !containItem(item)) {
        if (quantity > 64) {
          this->InvenContainer[i].setSlot(item, id, 64);
          quantity = quantity -  64;
        } else {
          this->InvenContainer[i].setSlot(item, id, quantity);
          quantity = 0;
        }
      } else if (temp != NULL && containItem(item)) {
        if (temp->getId() == item->getId()) {
          if (temp->isA<NonTool>()) {
            if (this->InvenContainer[i].getQuantity() + quantity <= 64) {
              this->InvenContainer[i].addQuantity(quantity);
              quantity = 0;
            } else {
              int quantityLeft = this->InvenContainer[i].getQuantity() + quantity;
              quantityLeft -= 64;
              quantity -= quantityLeft;
              this->InvenContainer[i].addQuantity(quantity);
              quantity = quantityLeft;
            }
          }
        }
      }
    } else {
      return;
    }
    id++;
  }
}

void Inventory::discardItem(string id, int quantity) {
  int idSlot = getIdFromString(id);

  if (this->InvenContainer[idSlot].getItem() == NULL) {
    throw Exception("This Slot is Empty!");
  }

  if (this->InvenContainer[idSlot].getQuantity() >= quantity) {
    if (this->InvenContainer[idSlot].getId() == idSlot) {
      this->InvenContainer[idSlot].reduceQuantity(quantity);
      if (this->InvenContainer[idSlot].getQuantity() == 0) {
        this->InvenContainer[idSlot].setEmptySlot();
      }
    }
  } else {
    throw Exception("Quantity to throw exceeds item quantity!");
  }
}

void Inventory::useTool(string id) {
  int idSlot = getIdFromString(id);

  Item* temp = this->InvenContainer[idSlot].getItem();

  if (temp == NULL) {
    throw Exception("This Slot is Empty!");
  }

  if (temp->isA<Tool>()) {
    Tool* t = dynamic_cast<Tool*>(temp);
    t->setDurability(t->getDurability() - 1);
    if (t->getDurability() == 0) {
      this->InvenContainer[idSlot].setEmptySlot();
    }
  } else {
    throw Exception("This item is not a tool!");
  }
}

void Inventory::showInventory() {
    int id = 0;
    for (int i = 0; i < 27; i++) {
        Item* temp = InvenContainer[i].getItem();
        if (temp == NULL) {
            if (id < 10) {
              cout << "[ I " << id << " ] ";
            } else {
              cout << "[ I" << id << " ] ";
            }
        } else if (temp->isA<NonTool>()) {
            NonTool* nt = dynamic_cast<NonTool*>(temp);
            cout << "[ " << nt->getName() << ";" << InvenContainer[i].getQuantity() << " ] ";
        } else {
            Tool* t = dynamic_cast<Tool*>(temp);
            cout << "[ " << t->getName() << ";" << t->getDurability() << " ] ";
        }
        id++;
        if ((i + 1) % 9 == 0) {
          cout << endl;
        }
    }
}

// Export inventory
void Inventory::testExport() {
  for (int i = 0; i < 27; i++) {
    Item* temp = InvenContainer[i].getItem();
    if (temp != NULL) {
      if (temp->isA<NonTool>()) {
        NonTool* nt = dynamic_cast<NonTool*>(temp);
        cout << nt->getId() << ":" << InvenContainer[i].getQuantity() << endl;
      } else {
        Tool* t = dynamic_cast<Tool*>(temp);
        cout << t->getId() << ":" << t->getDurability() << endl;
      }
    } else {
      cout << "0:0" << endl;
    }
  }
}

void Inventory::exportInventory(string outputPath) {
  ofstream outputFile(outputPath);

  for (int i = 0; i < 27; i++) {
    Item* temp = InvenContainer[i].getItem();
    if (temp != NULL) {
      if (temp->isA<NonTool>()) {
        NonTool* nt = dynamic_cast<NonTool*>(temp);
        outputFile << nt->getId() << ":" << InvenContainer[i].getQuantity() << endl;
      } else {
        Tool* t = dynamic_cast<Tool*>(temp);
        outputFile << t->getId() << ":" << t->getDurability() << endl;
      }
    } else {
      outputFile << "0:0" << endl;
    }
  }
}
