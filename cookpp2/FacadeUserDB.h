#pragma once
#include "PantryDBManager.h"
#include "RecipeDBManager.h"
#include "IngredientDBManager.h"

class FacadeUserDB
{
private:
	PantryDBManager * DBPantry;
	std::string DBPantryPath;
	RecipeDBManager* DBRecipe;
	std::string DBRecipePath;
	IngredientDBManager* DBIngredient;
	std::string DBIngredientPath;

public:
	FacadeUserDB();
	FacadeUserDB(std::string DBPantryPath, std::string DBRecipePath, std::string DBIngregientPath);
	FacadeUserDB(FacadeUserDB& c);
	~FacadeUserDB();

	bool getPantry(Pantry* pantryTarget);
	bool savePantry(Pantry* pantry);

	std::list<Recipe*> getAllRecipe();
	bool getRecipe(Recipe* recipeTarget,int pos);
	bool saveRecipe(Recipe* recipe,int pos);
	bool addRecipe(Recipe*);

	std::list<Ingredient*> getAllIngredient();
	Ingredient getIngredient(int pos);
	bool saveIngredient(Ingredient* ingredient, int pos);
	bool addIngredient(Ingredient*);


};

