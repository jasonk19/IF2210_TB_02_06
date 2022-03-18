#include "Recipe.hpp"
#include <fstream>

int Recipe::getRowEff() const{
    return this->rowEff;
}

int Recipe::getColEff() const{
    return this->colEff;
}

ItemID Recipe::getResultId() const{
    return this->resultId;
}

int Recipe::getResultCount() const{
    return this->resultCount;
}

Recipe::Recipe(string recipefile){
    ifstream configFile(recipefile);
    int row, col;
    configFile >> row >> col;
    
    for(int i = 0; i < row;){
        vector<ItemID> rowItem;
        bool isRowEmpty = true;
        for(int j = 0; j < col; j++){
            string temp;
            configFile >> temp;
            if(temp == "-"){
                rowItem.push_back(NO_ITEM);
            } else{
                isRowEmpty = false;
                rowItem.push_back(Item::nama_ItemIdMap.find(temp)->second);
            }
        }
        // Tidak memasukkan baris yang kosong
        if(isRowEmpty){
            row--;
        } else{
            this->recipe.push_back(rowItem);
            i++;
        }
    }
    // Mengecek dan menghapus kolom kosong
    for(int i = 0; i < col;){
        bool isColEmpty = true;
        // Mengecek kolom kosong
        for(int j = 0; j < row; j++){
            if(this->recipe[j][i] != NO_ITEM){
                isColEmpty = false;
                break;
            }
        }
        // Menghapus kolom kosong
        if(isColEmpty){
            col--;
            for(int j = 0; j < row; j++){
                this->recipe[j].erase(this->recipe[j].begin() + i);
            }
        } else{
            i++;
        }
    }

    string resultName;
    int resultCount;
    configFile >> resultName >> resultCount;
    this->resultCount = resultCount;
    this->resultId = Item::nama_ItemIdMap.find(resultName)->second;
    this->rowEff = row;
    this->colEff = col;

    configFile.close();
}

void Recipe::displayRecipe() const{
    for(int i = 0; i < this->rowEff; i++){
        for(int j = 0; j < this->colEff; j++){
            cout << this->recipe[i][j] << ' ';
        }
        cout << '\n';
    }
}