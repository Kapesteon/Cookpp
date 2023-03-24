#include "Ingredient.h"

Ingredient::Ingredient()
{
	this->name = "Undefined";
	this->type = "N/A";
	this->season = "N/A";
	this->infoNutri = new InfoNutri();
}

Ingredient::Ingredient(std::string name, std::string type, std::string season, InfoNutri *infoNutri)
{
	this->name = name;
	this->type = type;
	this->season = season;
	this->infoNutri = infoNutri;
}


Ingredient::Ingredient(const Ingredient& c)
{
	this->name = c.name;
	this->type = c.type;
	this->season = c.season;
	this->infoNutri = c.infoNutri;
}

Ingredient::~Ingredient()
{
	if (this->infoNutri == NULL) {
		OutputDebugStringA("InfoNutri in Ingredient aleady destroyed\n");
	} else {
		try {
			//delete this->infoNutri;
			this->infoNutri.reset();
		}
		catch (std::exception e) {
			OutputDebugStringA("Error while destroying Ingredient :");
			OutputDebugStringA(e.what());
		}
		OutputDebugStringA("Ingredient Destroyed \n");
	}

}

const std::string Ingredient::getName(void) const
{
	return std::string(this->name);
}

void Ingredient::setName(std::string name)
{
	this->name = name;
	return;
}

const std::string Ingredient::getType(void) const
{
	return std::string(this->type);
}

void Ingredient::setType(std::string type)
{
	this->type = type;
	return;
}

const std::string Ingredient::getSeason(void) const 
{
	return std::string(this->season);
}


void Ingredient::setSeason(std::string season)
{
	this->season = season;
	return;
}

InfoNutri * Ingredient::getInfoNutri(void) const
{

	return this->infoNutri;
}

void Ingredient::setInfoNutri(InfoNutri * infoNutri)
{
	this->infoNutri = infoNutri;
	return;
}


