#ifndef RECIPE_HPP
#define RECIPE_HPP

#include "../Item.hpp"
#include <vector>
using namespace std;

class Recipe{
    private:
        int rowEff, colEff;
        vector< vector<ItemID> > recipe;
        ItemID resultId;
        int resultCount;

    public:
        Recipe();
        Recipe(string recipeFile);
        Recipe(vector< vector<Item> > recipe);
        int getRowEff() const;
        int getColEff() const;
        ItemID getResultId() const;
        int getResultCount() const;
        bool match(const Recipe& match) const;
        void displayRecipe() const;
};

#endif