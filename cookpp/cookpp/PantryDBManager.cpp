#include "PantryDBManager.h"

PantryDBManager::PantryDBManager()
	: GenericDBManager() 
{
}

PantryDBManager::PantryDBManager(std::string filepath)
	: GenericDBManager(filepath) 
{
}

PantryDBManager::PantryDBManager(PantryDBManager& c)
{
	this->setFilePath(c.getFilepath());
}

PantryDBManager::~PantryDBManager()
{
	std::cout << "GenericDBManager Destroyed \n";
	OutputDebugStringA("GenericDBManager Destroyed \n");
}



bool PantryDBManager::write(void * pantry, int pos)//Pointer to Pantry object
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {
			this->stream.write((char*)pantry, this->classSize);
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
bool PantryDBManager::read(void * pantry,int pos)//Pointer to Pantry object
{
	//If we can open the DB and the path isn't Null
	if (this->open() && this->getFilepath() != "") {
		try {
			this->stream.seekp(0, std::ios::beg);
			this->stream.read((char*)pantry, sizeof(Pantry));
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

