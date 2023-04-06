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
	try {

		Pantry pReturn;
		if (this->DBPantry->read(&pReturn,0)) {
			return pReturn;
		}
		else {
			return Pantry();
		}
	}
	catch (std::exception) {
		std::cout << "Failed to get Pantry";
		return Pantry();
	}
}

bool FacadeUserDB::savePantry(Pantry* pantry)
{
	try{
		if (this->DBPantry->write(pantry,0)) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception) {
		std::cout << "Failed to save Pantry";
		return false;
	}
}

/*--------------------RECIPE------------------*/
std::list<Recipe*> FacadeUserDB::getAllRecipe()
{
	
	try {

		return this->DBRecipe->getAllRecipe();
	}
	catch (std::exception) {
		std::cout << "Failed to get all Recipe";
		return std::list<Recipe*>();
	}
}

Recipe FacadeUserDB::getRecipe(int pos)
{
	try {

		Recipe p;
		if (this->DBRecipe->read(&p,pos)) {
			return p;
		}
		else {
			return Recipe();
		}
	}
	catch (std::exception) {
		std::cout << "Failed to get Recipe";
		return Recipe();
	}
}

bool FacadeUserDB::saveRecipe(Recipe* recipe, int pos)
{
	try {

	
		if (this->DBRecipe->write(recipe,pos)) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception) {
		std::cout << "Failed to save Recipe";
		return false;
	}
}

bool FacadeUserDB::addRecipe(Recipe* recipe)
{
	try{
		if (this->DBRecipe->append(recipe)) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception) {
		std::cout << "Failed to add Recipe";
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
	try {
		Ingredient i;
		if (this->DBIngredient->read(&i, pos)) {
			return i;
		}
		else {
			return Ingredient();
		}
	}
	catch(std::exception){
		std::cout << "Failed to get Ingredient";
		return Ingredient();
	}

}

bool FacadeUserDB::saveIngredient(Ingredient* ingredient, int pos)
{
	try {


		if (this->DBIngredient->write(ingredient, pos)) {
			return true;
		}
		else {
			return false;
		}

	}

	catch (std::exception) {
		std::cout << "Failed to save Ingredient";
		return false;
}
}

bool FacadeUserDB::addIngredient(Ingredient* ingredient)
{
	try{
		if (this->DBIngredient->append(ingredient)) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception) {
		std::cout << "Failed to add Ingredient";
		return false;
	}
}