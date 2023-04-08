#pragma once
#include "GenericDBManager.h"
#include "Ingredient.h"
#include <list>
class IngredientDBManager :
    public GenericDBManager
{
    private:
        static const std::streamsize classSize = sizeof(Ingredient);
    public:

        IngredientDBManager();
        IngredientDBManager(std::string filepath);
        IngredientDBManager(IngredientDBManager& c);
        ~IngredientDBManager();


        bool write(void* ingredient, int pos); //Pointer to Ingredient object
        bool read(void* ingredient, int pos);  //Pointer to Ingredient object
        bool append(void* ingredient); //Pointer to Ingredient object

        std::list<Ingredient*> getAllIngredient();
 };


