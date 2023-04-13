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

FacadeUserDB::FacadeUserDB(std::string DBPantryPath, std::string DBRecipePath, std::string DBIngredientPath)
{
	this->DBPantryPath = DBPantryPath;
	this->DBPantry = new PantryDBManager(DBPantryPath);
	this->DBRecipePath = DBRecipePath;
	this->DBRecipe = new RecipeDBManager(this->DBRecipePath);
	this->DBIngredientPath = DBIngredientPath;
	this->DBIngredient = new IngredientDBManager(this->DBIngredientPath);
}

FacadeUserDB::FacadeUserDB(FacadeUserDB& c)
{
	this->DBPantry = c.DBPantry;
	this->DBPantryPath = c.DBPantryPath;
	this->DBRecipe = c.DBRecipe;
	this->DBRecipePath = c.DBRecipePath;
	this->DBIngredientPath = c.DBIngredientPath;
	this->DBIngredient = c.DBIngredient;

}

FacadeUserDB::~FacadeUserDB()
{
	delete this->DBPantry;
	delete this->DBRecipe;
	delete this->DBIngredient;
}




/*
/!\
FOR SOME REASON, FSTREAM.READ RETURNS ALREADY ALLOCATED HEAP MEMORY 
THIS MEANS THAT IF THERE IS 2 PANTRY SHARING AT LEAST ONE ITEM IN std::forward_list<StockedAliment*> stock
THEN THE PROGRAM WILL CRASH AS THE DESTRUCTOR WILL HAVE ALREADY DEALLOCATED THE FIRST ITEM THUS CRASHING ON THE SECOND TRY
*/
bool FacadeUserDB::getPantry(Pantry * pantryTarget)
{
	try {


		if (this->DBPantry->read(pantryTarget,0)) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception) {
		std::cout << "Failed to get Pantry";
		return false;
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

bool FacadeUserDB::getRecipe(Recipe* recipeTarget,int pos)
{
	try {


		if (this->DBRecipe->read(recipeTarget,pos)) {
			return true;
		}
		else {
			return false;
		}
	}
	catch (std::exception) {
		std::cout << "Failed to get Recipe";
		return false;
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

	try {

		return this->DBIngredient->getAllIngredient();
	}
	catch (std::exception) {
		std::cout << "Failed to get all Recipe";
		return std::list<Ingredient *>();
	}

}

int FacadeUserDB::getIngredientIndex(Ingredient* ingrToSearch)
{
	std::list<Ingredient*> allIngr = this->getAllIngredient();
	int i = 0;
	for (auto it = allIngr.begin(); it != allIngr.end(); it++) {
		if ((*it)->getName() == ingrToSearch->getName()) {
			return i;
		}
		i++;
	}
	return -1;
}


Ingredient FacadeUserDB::getIngredientByName(std::string name)
{
	auto listIngredient = this->getAllIngredient();
	for (auto it = listIngredient.begin(); it != listIngredient.end(); it++) {
		if ((*it)->getName() == name) {
			return **it;
		}
	}
	return Ingredient();
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