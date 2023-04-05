#include "RecipeDBManager.h"


RecipeDBManager::RecipeDBManager()
	: GenericDBManager()
{
}

RecipeDBManager::RecipeDBManager(std::string filepath)
	: GenericDBManager(filepath)
{
}

RecipeDBManager::RecipeDBManager(RecipeDBManager& c)
{
	this->setFilePath(c.getFilepath());
}

RecipeDBManager::~RecipeDBManager()
{
	std::cout << "GenericDBManager Destroyed \n";
	OutputDebugStringA("GenericDBManager Destroyed \n");
}



bool RecipeDBManager::write(void* recipe,int pos=0)//Pointer to recipe object
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {
			this->stream.seekp(pos * this->classSize, std::ios::beg);    //move the write ponter this time
			this->stream.write((char*)recipe, this->classSize);
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
bool RecipeDBManager::read(void* recipe, int pos=0)//Pointer to recipe object
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {

			this->stream.seekg(pos* this->classSize, std::ios::beg);
			//If we went too far off

			this->stream.read((char*)recipe, this->classSize);
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

bool RecipeDBManager::append(void* recipe)
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {
			this->stream.seekp(0,std::ios::end);    //move the write ponter this time
			this->stream.write((char*)recipe, this->classSize);
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

std::list<Recipe*> RecipeDBManager::getAllRecipe()
{
	std::list<Recipe*> returnList;
	unsigned int i = 0;

	while (i < 255) {
		Recipe* toPush = new Recipe();
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


