#include "Aliment.h"

Aliment::Aliment()
	: Ingredient()
{

	this->mass = 0;
}

Aliment::Aliment(std::string name, std::string type, std::string season, InfoNutri* infoNutri, double mass)
	: Ingredient(name, type, season, infoNutri) 
{

	this->mass = mass;
}

Aliment::Aliment(const Ingredient& ingr, double mass)
	: Ingredient(ingr)
{

	this->mass = mass;
}

Aliment::Aliment(const Aliment& c)
{
	this->setName(c.getName());
	this->setType(c.getType());
	this->setSeason(c.getSeason());
	this->setInfoNutri(c.getInfoNutri());
	this->mass = c.mass;
}

Aliment::~Aliment()
{
	OutputDebugStringA("Aliment Destroyed \n");
}

void Aliment::setMass(double mass)
{
	this->mass = mass;
	return;
}

double Aliment::getMass()
{
	return this->mass;
}
