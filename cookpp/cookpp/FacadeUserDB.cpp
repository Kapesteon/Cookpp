#include "FacadeUserDB.h"






FacadeUserDB::FacadeUserDB()
{
	this->DBPantryPath = "stockDB/pantry.cdb";
	this->DBpantry = new PantryDBManager(DBPantryPath);
}

FacadeUserDB::FacadeUserDB(std::string DBPantryPath)
{
	this->DBPantryPath = DBPantryPath;
	this->DBpantry = new PantryDBManager(DBPantryPath);
}

FacadeUserDB::FacadeUserDB(FacadeUserDB& c)
{
	this->DBpantry = c.DBpantry;
}

FacadeUserDB::~FacadeUserDB()
{
	delete this->DBpantry;
}

Pantry FacadeUserDB::getPantry()
{
	Pantry pReturn;
	if (this->DBpantry->read(&pReturn,0)) {
		return pReturn;
	}
	else {
		return Pantry();
	}

}

bool FacadeUserDB::savePantry(Pantry* pantry)
{

	if (this->DBpantry->write(pantry,0)) {
		return true;
	}
	else {
		return false;
	}
}

Recipe FacadeUserDB::getAllRecipe()
{
	return Recipe();
}

bool FacadeUserDB::saveRecipe(int pos, bool isNew)
{
	return false;
}

