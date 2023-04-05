#pragma once
#include "GenericDBManager.h"
#include "Recipe.h"
#include <list>

class RecipeDBManager :
    public GenericDBManager
{
private:
    static const std::streamsize classSize = sizeof(Recipe);
public:

    RecipeDBManager();
    RecipeDBManager(std::string filepath);
    RecipeDBManager(RecipeDBManager& c);
    ~RecipeDBManager();


    bool write(void* recipe, int pos); //Pointer to Recipe object
    bool read(void* recipe, int pos);  //Pointer to Recipe object
    bool append(void* recipe); //Pointer to Recipe object

    std::list<Recipe*> getAllRecipe();
};

