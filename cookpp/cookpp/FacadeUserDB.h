#pragma once
#include "PantryDBManager.h"
#include "RecipeDBManager.h"

class FacadeUserDB
{
private:
	PantryDBManager * DBpantry;
	std::string DBPantryPath;
public:
	FacadeUserDB();
	FacadeUserDB(std::string DBPantryPath);
	FacadeUserDB(FacadeUserDB& c);
	~FacadeUserDB();

	Pantry getPantry();
	bool savePantry(Pantry* pantry);
	Recipe getAllRecipe();
	bool saveRecipe(int pos, bool isNew);
};

