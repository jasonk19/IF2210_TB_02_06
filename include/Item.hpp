#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <iostream>
#include <string>
#include <map>
#include "Mapping.hpp"

typedef enum ItemID {
    NO_ITEM = 0
} ItemID;

using namespace std;

class Item {
    protected:
        int id;
        string name;
        string type;
    public:
        static Mapping<string,int> nama_ItemIdMap; // mapping nama dan enum ItemID, dari config
        static Mapping<int,Item*> itemId_ItemMap;  // menyimpan objek Item, jika ingin menambah suatu objek tinggal copy dari sini
        static Mapping<int,string> itemId_rawTypeMap;   // rawType: LOG, PLANK
        static Mapping<string,int> rawType_rawIdMap;        // memberi id tiap rawType
        static void readItemConfig(string configFile); // menginisialisasi namaItemIdMap dan itemIdItemMap
        static Item* generateObject(int itemId);

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
        template<typename T>
        bool isA(){
            return (dynamic_cast<T*>(this) != NULL);
        }
};

#endif