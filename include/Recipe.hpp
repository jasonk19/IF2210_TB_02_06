#ifndef RECIPE_HPP
#define RECIPE_HPP

#include "Item.hpp"
#include <vector>
using namespace std;

class Recipe{
    private:
        int rowEff, colEff;
        vector< vector<int> > recipe;
        int resultId;
        int resultCount;

    public:
        Recipe();
        Recipe(string recipeFile);
        Recipe(vector< vector<int> > recipe);  // Membuat recipe berdasarkan vector 2D ItemID
        int getRowEff() const;
        int getColEff() const;
        int getResultId() const;
        int getResultCount() const;
        int match(const Recipe& other) const;
        void displayRecipe() const;
};

#endif