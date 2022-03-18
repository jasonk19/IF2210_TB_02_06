#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include "Class.hpp"


class Crafting{
    protected: 
        // Atau recipe string aja mungkin? biar baca confignya gampang?
        // String recipe[3][3];
        string recipe_name; // buat baca config?
        NonTool recipe[3][3];
        NonTool crafting_table[3][3];

    public:

        // void craft();
        //void moveToInventory(Inventory inventory, string IDCraftsrc, string IDinvendest);
        //void showCrafting();




};
#endif