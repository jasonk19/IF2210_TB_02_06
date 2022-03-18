#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <iostream>
#include <string>

enum ItemID {
    OAK_LOG = 1,
    SPRUCE_LOG = 2,
    BIRCH_LOG = 3,
    OAK_PLANK = 4,
    SPRUCE_PLANK = 5,
    BIRCH_PLANK = 6,
    STICK = 7,
    COBBLESTONE = 8,
    BLACKSTONE = 9,
    IRON_INGOT = 10,
    IRON_NUGGET = 11,
    DIAMOND = 12,
    WOODEN_PICKAXE = 13,
    STONE_PICKAXE = 14,
    IRON_PICKAXE = 15,
    DIAMOND_PICKAXE = 16,
    WOODEN_AXE = 17,
    STONE_AXE = 18,
    IRON_AXE = 19,
    DIAMOND_AXE = 20,
    WOODEN_SWORD = 21,
    STONE_SWORD = 22,
    IRON_SWORD = 23,
    DIAMOND_SWORD = 24
};

using namespace std;

class Item {
    protected:
        int id;
        string name;
        string type;
    public:
        //CTOR, CCTOR, operator=, DTOR
        Item();
        Item(int id, string name, string type);
        Item(const Item& item);
        Item& operator=(const Item& item);
        virtual ~Item();

        // Getter
        int getId();
        string getName();
        string getType();

        // Setter
        void setId(int id);
        void setName(string name);
        void setType(string type);

        virtual void show() = 0;
};

#endif