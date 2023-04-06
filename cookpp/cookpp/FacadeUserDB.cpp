#include "FacadeUserDB.h"






FacadeUserDB::FacadeUserDB()
{
	this->DBPantryPath = "stockDB/pantry.cdb";
	this->DBPantry = new PantryDBManager(this->DBPantryPath);
	this->DBRecipePath = "stockDB/recipe.cdb";
	this->DBRecipe = new RecipeDBManager(this->DBRecipePath);
	this->DBIngredientPath = "stockDB/ingredient.cdb";
	this->DBIngredient = new IngredientDBManager(this->DBIngredientPath);
}

FacadeUserDB::FacadeUserDB(std::string DBPantryPath, std::string DBRecipePath, std::string DBIngregientPath)
{
	this->DBPantryPath = DBPantryPath;
	this->DBPantry = new PantryDBManager(DBPantryPath);
	this->DBRecipePath = "stockDB/recipe.cdb";
	this->DBRecipe = new RecipeDBManager(this->DBRecipePath);
}

FacadeUserDB::FacadeUserDB(FacadeUserDB& c)
{
	this->DBPantry = c.DBPantry;
	this->DBPantryPath = c.DBPantryPath;
	this->DBRecipe = c.DBRecipe;
	this->DBRecipePath = c.DBRecipePath;

}

FacadeUserDB::~FacadeUserDB()
{
	delete this->DBPantry;
	delete this->DBRecipe;
}

Pantry FacadeUserDB::getPantry()
{
	Pantry pReturn;
	if (this->DBPantry->read(&pReturn,0)) {
		return pReturn;
	}
	else {
		return Pantry();
	}

}

bool FacadeUserDB::savePantry(Pantry* pantry)
{

	if (this->DBPantry->write(pantry,0)) {
		return true;
	}
	else {
		return false;
	}
}

/*--------------------RECIPE------------------*/
std::list<Recipe*> FacadeUserDB::getAllRecipe()
{
	
	return this->DBRecipe->getAllRecipe();
}

Recipe FacadeUserDB::getRecipe(int pos)
{
	Recipe p;
	if (this->DBRecipe->read(&p,pos)) {
		return p;
	}
	else {
		return Recipe();
	}
}

bool FacadeUserDB::saveRecipe(Recipe* recipe, int pos)
{
	if (this->DBRecipe->write(recipe,pos)) {
		return true;
	}
	else {
		return false;
	}
}

bool FacadeUserDB::addRecipe(Recipe* recipe)
{
	if (this->DBRecipe->append(recipe)) {
		return true;
	}
	else {
		return false;
	}
}



/*--------------------Ingredient------------------*/
std::list<Ingredient*> FacadeUserDB::getAllIngredient()
{

	return this->DBIngredient->getAllIngredient();
}

Ingredient FacadeUserDB::getIngredient(int pos)
{
	Ingredient i;
	if (this->DBIngredient->read(&i, pos)) {
		return i;
	}
	else {
		return Ingredient();
	}
}

bool FacadeUserDB::saveIngredient(Ingredient* ingredient, int pos)
{
	if (this->DBIngredient->write(ingredient, pos)) {
		return true;
	}
	else {
		return false;
	}
}

bool FacadeUserDB::addIngredient(Ingredient* ingredient)
{
	if (this->DBIngredient->append(ingredient)) {
		return true;
	}
	else {
		return false;
	}
}