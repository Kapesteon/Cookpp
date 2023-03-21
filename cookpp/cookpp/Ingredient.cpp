#include "Ingredient.h"

Ingredient::Ingredient()
{
}

Ingredient::Ingredient(std::string name, std::string type, std::string season, InfoNutri &infoNutri)
{
}


Ingredient::Ingredient(Ingredient& c)
{
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


