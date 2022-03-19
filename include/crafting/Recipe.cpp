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

Recipe::Recipe(vector<vector<ItemID> > recipe){
    int row = recipe.size();
    int col = recipe[0].size();

    vector<bool> isEmpty = {true, true, true};
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(recipe[i][j] != NO_ITEM){
                isEmpty[i] = false;
                break;
            }
        }
    }
    // Kalau baris 1 atau 3 ada yang kosong, aman untuk menghapus baris tengah
    bool isMiddleSafe = isEmpty[0] || isEmpty[2];
    if(isMiddleSafe){
        for(int i = 0; i < row;){
            if(isEmpty[i]){
                row--;
                recipe.erase(recipe.begin() + i);
                isEmpty.erase(isEmpty.begin() + i);
            } else{
                i++;
            }
        }
    }

    // Mengecek dan menghapus kolom kosong
    isEmpty = {true, true, true};
    for(int i = 0; i < col; i++){
        // Mengecek kolom kosong
        for(int j = 0; j < row; j++){
            if(recipe[j][i] != NO_ITEM){
                isEmpty[i] = false;
                break;
            }
        }
    }
    isMiddleSafe = isEmpty[0] || isEmpty[2];
    if(isMiddleSafe){
        for(int i = 0; i < col;){
            if(isEmpty[i]){
                col--;
                for(int j = 0; j < row; j++){
                    recipe[j].erase(recipe[j].begin() + i);
                }
                isEmpty.erase(isEmpty.begin() + i);
            } else{
                i++;
            }
        }
    }
    this->rowEff = row;
    this->colEff = col;
    this->recipe = recipe;
}

Recipe::Recipe(string recipefile){
    ifstream configFile(recipefile);
    int row, col;
    configFile >> row >> col;
    
    vector<bool> isEmpty = {true, true, true};
    for(int i = 0; i < row; i++){
        vector<ItemID> rowItem;
        for(int j = 0; j < col; j++){
            string temp;
            configFile >> temp;
            if(temp == "-"){
                rowItem.push_back(NO_ITEM);
            } else{
                isEmpty[i] = false;
                auto resId = Item::nama_ItemIdMap.find(temp);
                if(resId != Item::nama_ItemIdMap.end()){
                    rowItem.push_back(resId->second);
                } else{
                    rowItem.push_back((ItemID)Item::rawType_rawIdMap.find(temp)->second);
                }
            }
        }
        this->recipe.push_back(rowItem);
    }
    // Kalau baris 1 atau 3 ada yang kosong, aman untuk menghapus baris tengah
    bool isMiddleSafe = isEmpty[0] || isEmpty[2];
    if(isMiddleSafe){
        for(int i = 0; i < row;){
            if(isEmpty[i]){
                row--;
                this->recipe.erase(this->recipe.begin() + i);
                isEmpty.erase(isEmpty.begin() + i);
            } else{
                i++;
            }
        }
    }

    // Mengecek dan menghapus kolom kosong
    isEmpty = {true, true, true};
    for(int i = 0; i < col; i++){
        // Mengecek kolom kosong
        for(int j = 0; j < row; j++){
            if(this->recipe[j][i] != NO_ITEM){
                isEmpty[i] = false;
                break;
            }
        }
    }
    isMiddleSafe = isEmpty[0] || isEmpty[2];
    if(isMiddleSafe){
        for(int i = 0; i < col;){
            if(isEmpty[i]){
                col--;
                for(int j = 0; j < row; j++){
                    this->recipe[j].erase(this->recipe[j].begin() + i);
                }
                isEmpty.erase(isEmpty.begin() + i);
            } else{
                i++;
            }
        }
    }

    string resultName;
    int resultCount;
    configFile >> resultName >> resultCount;
    this->resultCount = resultCount;
    
    auto resId = Item::nama_ItemIdMap.find(resultName);
    if(resId != Item::nama_ItemIdMap.end()){
        this->resultId = resId->second;
    } else{
        this->resultId = (ItemID)Item::rawType_rawIdMap.find(resultName)->second;
    }
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

bool Recipe::match(const Recipe& other) const{
    if(this->rowEff != other.rowEff) return false;
    if(this->colEff != other.colEff) return false;

    bool same = true;
    int row = this->rowEff;
    int col = this->colEff;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            ItemID thisId = this->recipe[i][j];
            ItemID otherId = other.recipe[i][j];
            auto thisRawType = Item::itemId_rawTypeMap.find(thisId);
            auto otherRawType = Item::itemId_rawTypeMap.find(otherId);

            if(otherRawType == Item::itemId_rawTypeMap.end() && thisRawType == Item::itemId_rawTypeMap.end()){
                if(thisId != otherId){
                    same = false;
                    break;
                }
            } else if(thisRawType == Item::itemId_rawTypeMap.end()){
                int otherRawId = Item::rawType_rawIdMap.find(otherRawType->second)->second;
                if(thisId != otherId && thisId != otherRawId){
                    same = false;
                    break;
                }
            } else if(otherRawType == Item::itemId_rawTypeMap.end()){
                int thisRawId = Item::rawType_rawIdMap.find(thisRawType->second)->second;
                if(thisId != otherId && thisRawId != otherId){
                    same = false;
                    break;
                }
            } else{
                int thisRawId = Item::rawType_rawIdMap.find(thisRawType->second)->second;
                int otherRawId = Item::rawType_rawIdMap.find(otherRawType->second)->second;
                if(thisId != otherId && thisRawId != otherId && thisId != otherRawId && thisRawId != otherRawId){
                    same = false;
                    break;
                }
            }
        }
        if(!same) break;
    }
    if(!same){  // cek mirror sumbu y
        same = true;
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                ItemID thisId = this->recipe[i][j];
                ItemID otherId = other.recipe[i][col-j-1];
                auto thisRawType = Item::itemId_rawTypeMap.find(thisId);
                auto otherRawType = Item::itemId_rawTypeMap.find(otherId);

                if(otherRawType == Item::itemId_rawTypeMap.end() && thisRawType == Item::itemId_rawTypeMap.end()){
                    if(thisId != otherId){
                        same = false;
                        break;
                    }
                } else if(thisRawType == Item::itemId_rawTypeMap.end()){
                    int otherRawId = Item::rawType_rawIdMap.find(otherRawType->second)->second;
                    if(thisId != otherId && thisId != otherRawId){
                        same = false;
                        break;
                    }
                } else if(otherRawType == Item::itemId_rawTypeMap.end()){
                    int thisRawId = Item::rawType_rawIdMap.find(thisRawType->second)->second;
                    if(thisId != otherId && thisRawId != otherId){
                        same = false;
                        break;
                    }
                } else{
                    int thisRawId = Item::rawType_rawIdMap.find(thisRawType->second)->second;
                    int otherRawId = Item::rawType_rawIdMap.find(otherRawType->second)->second;
                    if(thisId != otherId && thisRawId != otherId && thisId != otherRawId && thisRawId != otherRawId){
                        same = false;
                        break;
                    }
                }
            }
            if(!same) break;
        }
    }

    return same;
}