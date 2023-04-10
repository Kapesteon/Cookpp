#include "IngredientDBManager.h"


IngredientDBManager::IngredientDBManager()
	: GenericDBManager()
{
}

IngredientDBManager::IngredientDBManager(std::string filepath)
	: GenericDBManager(filepath)
{
}

IngredientDBManager::IngredientDBManager(IngredientDBManager& c)
{
	this->setFilePath(c.getFilepath());
}

IngredientDBManager::~IngredientDBManager()
{
	std::cout << "IngredientDBManager Destroyed \n";
	OutputDebugStringA("IngredientDBManager Destroyed \n");
}



bool IngredientDBManager::write(void* ingredient, int pos = 0)//Pointer to ingredient object
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {
			this->stream.seekp(pos * this->classSize, std::ios::beg);    //move the write ponter this time
			this->stream.write((char*)ingredient, this->classSize);
			this->close();
			return true;
		}
		catch (std::exception) {
			return false;
		}
	}
	else {
		return false;
	}

}

//read and Allocate return data to pointer
bool IngredientDBManager::read(void* ingredient, int pos = 0)//Pointer to ingredient object
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {

			this->stream.seekg(pos * this->classSize, std::ios::beg);
			this->stream.read((char*)ingredient, this->classSize);
			this->close();
			if (this->stream.eof()) {
				return false;
			}
			return true;
		}
		catch (std::exception) {
			return false;
		}
	}
	else {
		return false;
	}
}

bool IngredientDBManager::append(void* ingredient)
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {
			this->stream.seekp(0, std::ios::end);    //move the write ponter this time
			this->stream.write((char*)ingredient, this->classSize);
			this->close();
			return true;
		}
		catch (std::exception) {
			return false;
		}
	}
	else {
		return false;
	}
}

std::list<Ingredient*> IngredientDBManager::getAllIngredient()
{
	std::list<Ingredient*> returnList;
	unsigned int i = 0;

	while (i < 255) {
		Ingredient* toPush = new Ingredient();
		//Recipe toPush = Recipe();
		this->read(toPush, i);
		if (this->stream.eof()) {
			break;
		}
		returnList.push_back(toPush);
		i++;
	}
	return returnList;
}


