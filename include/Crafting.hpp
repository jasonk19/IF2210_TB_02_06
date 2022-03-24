#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "Item.hpp"
#include "Inventory.hpp"
#include "Recipe.hpp"

int getRowCraft(int integer);
int getColCraft(int integer);

//forward declaration
class Inventory;

class Crafting{
    protected: 
        vector<Recipe> recipes;
        Item* crafting_table[3][3];

    public:
        // void craft();
        
        void showCrafting();
        Crafting();
        ~Crafting();
        void addRecipe(Recipe r);
        Item* craft();          // craft dengan mengurangi item, implementasi memanggil craftSimulate
        Item* craftSimulate();  // craftSimulate adalah craft dengan tidak mengurangi item, untuk showCrafting
        Item* getItem(int i, int j) const;
        void setItem(Item* itm, int i, int j);
        vector<Recipe> getRecipes() const;
        void moveToInventory(Inventory& inventory, string IDCraftsrc, string IDinvendest);
};

#endif
