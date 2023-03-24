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

std::string Ingredient::getName(void)
{
	return std::string(this->name);
}

void Ingredient::setName(std::string name)
{
	this->name = name;
	return;
}

std::string Ingredient::getType(void)
{
	return std::string(this->type);
}

void Ingredient::setType(std::string type)
{
	this->type = type;
	return;
}

std::string Ingredient::getSeason(void)
{
	return std::string(this->season);
}


void Ingredient::setSeason(std::string season)
{
	this->season = season;
	return;
}

InfoNutri * Ingredient::getInfoNutri(void)
{

	return this->infoNutri;
}

void Ingredient::setInfoNutri(InfoNutri * infoNutri)
{
	this->infoNutri = infoNutri;
	return;
}


