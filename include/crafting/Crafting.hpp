#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "Class.hpp"
#include "Recipe.hpp"

class Crafting{
    protected: 
        // Atau recipe string aja mungkin? biar baca confignya gampang?
        // String recipe[3][3];
        vector<Recipe> recipes;
        Item* crafting_table[3][3];

    public:
        // void craft();
        // void moveToInventory(Inventory inventory, string IDCraftsrc, string IDinvendest);
        void showCrafting();
        Crafting();
        ~Crafting();
        void addRecipe(Recipe r);
        Item* craft();          // craft dengan mengurangi item, implementasi memanggil craftSimulate
        Item* craftSimulate();  // craftSimulate adalah craft dengan tidak mengurangi item, untuk showCrafting
};

#endif