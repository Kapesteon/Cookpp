#include "GenericDBManager.h"


GenericDBManager::GenericDBManager()
{
	this->setFilePath("");
}

GenericDBManager::GenericDBManager(std::string filepath)
{
	this->setFilePath(filepath);
}

GenericDBManager::GenericDBManager(GenericDBManager& c)
{
	this->setFilePath(c.getFilepath());
}

GenericDBManager::~GenericDBManager()
{
	std::cout << "GenericDBManager Destroyed \n";
	//OutputDebugStringA("GenericDBManager Destroyed \n");
}

void GenericDBManager::setFilePath(std::string filepath)
{
	this->filepath = filepath;
}

std::string GenericDBManager::getFilepath() const
{
	return this->filepath;
}

bool GenericDBManager::open()
{
	try {
		this->stream.open(this->getFilepath(), std::ios::in | std::ios::out | std::ios::binary);
		return true;
	}
	catch(std::exception){
		return false;
	}
}

bool GenericDBManager::close()
{
	try {
		this->stream.close();
		return true;
	}
	catch (std::exception) {
		return false;
	}
}
